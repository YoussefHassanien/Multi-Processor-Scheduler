#include "FCFS.h"
LinkedQueue<SIGKILL*> FCFS::KillingSignalsList;
//Constructor
FCFS::FCFS(Scheduler*Sptr,int forkprob, int id): Processor(Sptr),ForkProb(forkprob)
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
void FCFS::ScheduleAlgo(int TimeStep)
{
	int TempID = 0;
	Process* TempProcess = nullptr;
	Process* KilledProcess = nullptr;
	IO* TempIO = nullptr;
	SIGKILL* TempKillSig = nullptr;
	int RandomForkProb = s->generaterandom(1, 100);

	if (RDYList.isEmpty() && !RUNNING) // if there is nothing in the ready list and no process is running
		return;
	KillingSignalsList.peek(TempKillSig);
	if (TempKillSig)
	{
		int position = 0;

		if (TempKillSig->getTime() == TimeStep)
		{
			if (RDYListIDs.Find(TempKillSig->getID(), position))
			{
				int id = 0;  //dummy integer
				KillingSignalsList.dequeue(TempKillSig);
				RDYList.DeleteNodeAtPosition(KilledProcess, position);
				RDYListIDs.DeleteNodeAtPosition(id, position);
				s->ParentKilling(KilledProcess); //Killing the orphans operation
				processescount--;
			}
		}
	}
	
	if ((!isbusy) && (!RDYList.isEmpty())) //sets a process as running if the processor is idle
	{
		FCFStoRR_Migration(TimeStep);
		RDYList.DeleteFirst(TempProcess);
		if (TempProcess) {
			RDYListIDs.DeleteFirst(TempID);
			processescount--;
			TempProcess->SetRT(TimeStep);
			RUNNING = TempProcess;
			isbusy = true;                                  //Set the processor as busy
			s->incrementRunningCount();
		}
			if (RandomForkProb > 0 && RandomForkProb <= ForkProb) //Forking condition
				s->IntiateForking(RUNNING); //Forking operation
			KillingSignalsList.peek(TempKillSig);
			if (TempKillSig)
			{
				if (TempKillSig->getTime() == TimeStep) //Killing Signals Operation
				{
					if (TempKillSig->getID() == *RUNNING)
					{
						KillingSignalsList.dequeue(TempKillSig);
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
	else if (isbusy && RUNNING->GetCT()) //Same as if RUNNING->GetCT!=0
	{
		RUNNING->DecrementCT();
		TotalBT++;
		RUNNING->IncrementRunningFor();
		if (RandomForkProb > 0 && RandomForkProb <= ForkProb)
			s->IntiateForking(RUNNING); //Forking operation
		KillingSignalsList.peek(TempKillSig);
		if (TempKillSig)
		{
			if (TempKillSig->getTime() == TimeStep) //Killing Signals Operation
			{
				if (TempKillSig->getID() == *RUNNING)
				{
					KillingSignalsList.dequeue(TempKillSig);
					s->ParentKilling(RUNNING); //Killing the orphans operation
					isbusy = false;
					RUNNING = nullptr;
					//increment el idle ??
					//TotalIT++;
					s->DecrementRunningCount();
				}
			}
			else if (RUNNING->GetN())	/* the condition is same as if RUNNING->GetN()!=0 , 
				                         decrements the IO_R while the process is running*/ 
			{
				RUNNING->GetFirstIO(TempIO);
				if (TempIO)
				{
					if (TempIO->GetRequest() >= 0)
					{
						TempIO->DecrementIO_R();
					}


					if (TempIO->GetRequest() == -1)
					{
						s->addtoblocklist(RUNNING);
						isbusy = false;
						RUNNING = nullptr;
						s->DecrementRunningCount();
					}
				}
			}
		}
		else if (RUNNING->GetN())	/* the condition is same as if RUNNING->GetN()!=0 , 
				                         decrements the IO_R while the process is running*/ 
		{
			RUNNING->GetFirstIO(TempIO);
			if (TempIO)
			{
				if (TempIO->GetRequest() >= 0)
				{
					TempIO->DecrementIO_R();
				}
				if (TempIO->GetRequest() == -1)
				{
					s->addtoblocklist(RUNNING);
					isbusy = false;
					RUNNING = nullptr;
					s->DecrementRunningCount();
				}
			}
		}
	}	
	else if (isbusy && !RUNNING->GetCT()) //same as if RUNNING->GetCT==0
	{
		s->ParentKilling(RUNNING); //Killing the orphans operation
		isbusy = false;
		RUNNING = nullptr;
		//increment el idle ??
		TotalIT++;

		s->DecrementRunningCount();
	}
}


//Controls the process migration from FCFS processor to RR processor
void FCFS::FCFStoRR_Migration(int timestep)
{
	 
	Process *p=nullptr;
	RDYList.peek(p);
	if (p) 
	{
		if (p->WTsofar(timestep) < s->GetMaxW())
		{
			RDYList.DeleteFirst(p);
			processescount--;
			s->FromFCFStoShortestRR(p);
			//FCFStoRR_Migration(timestep);
		}
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
			RDYList.DeleteFirst(p);
			TotalCT = TotalCT + p->GetCT();
			RDYList.InsertEnd(p);
		}
		return TotalCT;
}

 void FCFS::AddKillingSignal(SIGKILL* killsignal)
 {
	 KillingSignalsList.enqueue(killsignal);
 }
//destructor
FCFS::~FCFS()
{
	
}

