#include "FCFS.h"
LinkedQueue<SIGKILL*> FCFS::KillingSignalsList;
//Constructor
FCFS::FCFS(Scheduler*Sptr,int id): Processor(Sptr)
{
	ID = id;
}

//adds a process in the ready list
void FCFS::AddToRdy(Process* p)
{
	RDYList.InsertEnd(p);
	processescount++;
	AddToRdyIDs(p);
}

//Adds a process ID to RDYListIDs
void FCFS::AddToRdyIDs(Process* p)
{
	RDYListIDs.InsertEnd(p->GetID());
}

//removes a node from the list
void FCFS::DeleteProcess(Process*& p)
{
	RDYList.DeleteFirst(p);
	processescount--;
	DeleteProcessID(p);
}

void FCFS::DeleteProcessAtPosition(Process*& p)
{
	RDYList.DeleteNode(p);
	processescount--;
}

//Deletes a process ID from RDYListIDs
void FCFS::DeleteProcessID(Process* p)
{
	int y=0;
	RDYListIDs.DeleteFirst(y);
}




//Prints ready list processes
void FCFS::Print_List()
{
	RDYList.PrintList();
}

//Returns the processor type
string FCFS::Get_Processor_Type()
{
	return "[FCFS]";
}

//Returns the number of processes in the ready list
int FCFS::GetRDYListCount()
{
	return RDYList.NodesCounter;
}

//Schedueling algorithm
void FCFS::ScheduleAlgo()
{
	Process* tmp = nullptr;
	Process* KilledProcess = NULL;
	IO* ioTemp = nullptr;
	SIGKILL* TempKillSig = nullptr;
	int RandomForkProb = s->generaterandom(1, 100);

	if (RDYList.isEmpty() && !RUNNING) // if there is nothing in the ready list and no process is running
		return;
	KillingSignalsList.peek(TempKillSig);
	if (TempKillSig)
	{
		int position = 0;

		if (s->CheckKillSigTime(TempKillSig))
		{
			if (RDYListIDs.Find(TempKillSig->getID(), position))
			{
				int id = 0;  //dummy integer
				KillingSignalsList.dequeue(TempKillSig);
				RDYList.DeleteNodeAtPosition(KilledProcess, position);
				RDYListIDs.DeleteNodeAtPosition(id, position);
				s->addToTrm(KilledProcess);
				s->ParentKilling(KilledProcess); //Killing the orphans operation
				processescount--;
			}
		}
	}
	
	if (!isbusy) //sets a process as running if the processor is idle
	{
		DeleteProcess(tmp);
		tmp->SetRT(s->getTimeStep());
		RUNNING = tmp;
		isbusy = true;                                  //Set the processor as busy
		s->incrementRunningCount();
		if (RandomForkProb > 0 && RandomForkProb <= s->getForkProb()) //Forking condition
			s->IntiateForking(RUNNING); //Forking operation
		KillingSignalsList.peek(TempKillSig);
		if (TempKillSig)
		{
			if (s->CheckKillSigTime(TempKillSig)) //Killing Signals Operation
			{
				KillingSignalsList.dequeue(TempKillSig);
				if (TempKillSig->getID() == *RUNNING)
				{
					s->addToTrm(RUNNING);
					s->ParentKilling(RUNNING); //Killing the orphans operation
					isbusy = false;
					RUNNING = nullptr;
					//increment el idle ??
					//TotalIT++;
					s->DecrementRunningCount();
				}
			}
		}

		return;
	}
	else if (isbusy && RUNNING->GetCT() != 0) 
	{
		RUNNING->DecrementCT();
		TotalBT++;
		RUNNING->IncrementRunningFor();
		if (RandomForkProb > 0 && RandomForkProb <= s->getForkProb())
			s->IntiateForking(RUNNING); //Forking operation
		KillingSignalsList.peek(TempKillSig);
		if (TempKillSig)
		{
			if (s->CheckKillSigTime(TempKillSig)) //Killing Signals Operation
			{
				KillingSignalsList.dequeue(TempKillSig);
				if (TempKillSig->getID() == *RUNNING)
				{
					s->addToTrm(RUNNING);
					s->ParentKilling(RUNNING); //Killing the orphans operation
					isbusy = false;
					RUNNING = nullptr;
					//increment el idle ??
					//TotalIT++;
					s->DecrementRunningCount();
				}
			}
			else if (RUNNING->GetN() != 0)						// decrements the IO_R while the process is running
			{
				RUNNING->GetFirstIO(ioTemp);
				if (ioTemp)
				{
					if (ioTemp->GetRequest() >= 0)
					{
						ioTemp->DecrementIO_R();
					}


					if (ioTemp->GetRequest() == -1)
					{
						s->addtoblocklist(RUNNING);
						isbusy = false;
						RUNNING = nullptr;
						s->DecrementRunningCount();
					}
				}
			}
		}
		else if (RUNNING->GetN() != 0)						// decrements the IO_R while the process is running
		{
			RUNNING->GetFirstIO(ioTemp);
			if (ioTemp)
			{
				if (ioTemp->GetRequest() >= 0)
				{
					ioTemp->DecrementIO_R();
				}


				if (ioTemp->GetRequest() == -1)
				{
					s->addtoblocklist(RUNNING);
					isbusy = false;
					RUNNING = nullptr;
					s->DecrementRunningCount();
				}
			}
		}
	}	
	else if (isbusy && RUNNING->GetCT() == 0)
	{
		s->addToTrm(RUNNING);
		s->ParentKilling(RUNNING); //Killing the orphans operation
		isbusy = false;
		RUNNING = nullptr;
		//increment el idle ??
		TotalIT++;
		s->DecrementRunningCount();
	}
}


//Controls the process migration from FCFS processor to RR processor
void FCFS::FCFStoRR_Migration()
{
	 
	Process *p;
	RDYList.peek(p);
	if (p->WTsofar() < s->GetMaxW())
	{
		RDYList.DeleteFirst(p);
		s->FromFCFStoShortestRR(p);
		FCFStoRR_Migration();
	}
}

bool FCFS::Search(Process* value)
{
	int x=0;
	return RDYList.Find(value,x);
}

int FCFS::SumCT()
{
		Process* p;
		for (int i = 0; i < processescount; i++)
		{
			RDYList.IterativePeek(p, i + 1);
			TotalCT += p->GetCT();
		}
		return (TotalCT);
}

 void FCFS::AddKillingSignal(SIGKILL* killsignal)
 {
	 KillingSignalsList.enqueue(killsignal);
 }
//destructor
FCFS::~FCFS()
{
	
}

