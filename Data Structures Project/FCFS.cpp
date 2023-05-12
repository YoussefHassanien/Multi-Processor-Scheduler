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
	RDYList.DeleteNode(p);
	processescount--;
	DeleteProcessID(p);
}

//Deletes a process ID from RDYListIDs
void FCFS::DeleteProcessID(Process* p)
{
	int y = p->GetID();
	RDYListIDs.DeleteNode(y);
}


//Picks a process randomly to terminate it
bool FCFS::RandomTermination(int id)
{
	int position = RDYListIDs.Find(id);
	Process* p=nullptr;
	
	if (position!=0)
	{
		int i=0;
		RDYListIDs.DeleteNodeAtPosition(i, position);
		RDYList.DeleteNodeAtPosition(p,position);
		s->addToTrm(p);
		return true;
	}
	return false;
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
	IO* ioTemp = nullptr;
	SIGKILL* TempKillSig = nullptr;
	int RandomForkProb = s->generaterandom(1, 100);

	if (RDYList.isEmpty() && !RUNNING) // if there is nothing in the ready list and no process is running
		return;
	KillingSignalsList.peek(TempKillSig);
	if (TempKillSig)
	{
		TempKillSig->DecrementKillTime();
	 }
	//	if (TempKillSig->getTime() == 0)
	//	{
	//		KillingSignalsList.dequeue(TempKillSig);
	//		if (RDYList.Find(TempKillSig->getID()))
	//		{

	//		}
	//	}
	//}
	if (!isbusy) //sets a process as running if the processor is idle
	{
		RDYList.DeleteFirst(tmp);
		processescount--;
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
			if (TempKillSig->getTime() == 0) //Killing Signals Operation
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
	else if (isbusy && RUNNING->GetCT() != 0) //keda lama btdkhol running mesh h decrement l ct fl time step di??
	{
		RUNNING->DecrementCT();
		TotalBT++;
		RUNNING->IncrementRunningFor();
		if (RandomForkProb > 0 && RandomForkProb <= s->getForkProb())
			s->IntiateForking(RUNNING); //Forking operation
		KillingSignalsList.peek(TempKillSig);
		if (TempKillSig)
		{
			if (TempKillSig->getTime() == 0) //Killing Signals Operation
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
	return RDYList.Find(value);
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

