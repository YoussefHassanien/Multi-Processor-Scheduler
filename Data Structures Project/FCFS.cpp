#include "FCFS.h"
LinkedQueue<SIGKILL*> FCFS::KillingSignalsList;
bool FCFS::KillSigFound;
//Constructor
FCFS::FCFS(Scheduler*Sptr,int forkprob, int id): Processor(Sptr),ForkProb(forkprob)
{
	ID = id;
	KillSigFound = false;          //sets it initially to false 
}

//adds a process in the ready list
void FCFS::AddToRdy(Process* p)
{
	RDYList.InsertEnd(p);
	processescount++;
	TotalCT = TotalCT + p->GetCT();
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
	TotalCT = TotalCT - p->GetCT();
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
void FCFS::ScheduleAlgo(int &TimeStep, int& stoptime)
{
	int TempID = 0;
	Process* TempProcess = nullptr;
	Process* KilledProcess = nullptr;
	IO* TempIO = nullptr;
	SIGKILL* TempKillSig = nullptr;
	int RandomForkProb = s->generaterandom(1, 100);
	if (isoverheating)
	{
		if (StoppedFor < stoptime)
			StoppedFor++;
		else if (StoppedFor == stoptime)
		{
			isoverheating = false;
			StoppedFor = 0;
		}
		return;
	}
	if (RDYList.isEmpty())
		TotalCT = 0;

	if (NothingToExecute()) //if there is nothing in the ready list and no running process
	{
		TotalIT++;
		return;
	}
	else
		TotalBT++;
		
	if ((!isbusy) && (!RDYList.isEmpty())) //sets a process as running if the processor is idle
	{
		FCFStoRR_Migration(TimeStep);
		RDYList.DeleteFirst(TempProcess);
		if (TempProcess) 
		{
			RDYListIDs.DeleteFirst(TempID);
			processescount--;
			TempProcess->SetRT(TimeStep);
			RUNNING = TempProcess;
			isbusy = true;                                  //Set the processor as busy
			s->incrementRunningCount();

			if (RandomForkProb > 0 && RandomForkProb <= ForkProb) //Forking condition
				s->IntiateForking(RUNNING); //Forking operation
		}
	}
	else if (isbusy && RUNNING->GetCT()) //Same as if RUNNING->GetCT!=0
	{
		RUNNING->DecrementCT();
		RUNNING->IncrementRunningFor();

		if (RandomForkProb > 0 && RandomForkProb <= ForkProb)
			s->IntiateForking(RUNNING); //Forking operation

		 if (RUNNING->GetN())	/* the condition is same as if RUNNING->GetN()!=0 , 
				                         decrements the IO_R while the process is running*/ 
		 {
			RUNNING->GetFirstIO(TempIO);
			if (TempIO)
			{
				if (TempIO->GetRequest() == RUNNING->GetRunningFor())
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
		s->addToTrm(RUNNING);
		s->ChildrenKilling(RUNNING); //Killing the orphans operation
		isbusy = false;
		RUNNING = nullptr;
		s->DecrementRunningCount();
	}
}


//Controls the process migration from FCFS processor to RR processor
void FCFS::FCFStoRR_Migration(int timestep)
{
	Process* p = nullptr;
	while (RDYList.peek(p) && !p->GetParent() && p->WTsofar(timestep) > s->GetMaxW())
	{
		RDYList.DeleteFirst(p);
		processescount--;
		s->FromFCFStoShortestRR(p);
		s->IncrementMaxW();
	}
	 
}

bool FCFS::Search(Process* value)
{
	int x=0;
	return RDYList.Find(value,x);
}



 void FCFS::AddKillingSignal(SIGKILL* killsignal)
 {
	 KillingSignalsList.enqueue(killsignal);
 }

 void FCFS::EmptyProcessor()
 {
	 if (RUNNING)
	 {
		 s->AddToShortestRdyList(RUNNING);
		 RUNNING = NULL;
		 isbusy = false;
		 s->DecrementRunningCount();
	 }
	 while (!RDYList.isEmpty())
	 {
		 Process* p = nullptr;
		 RDYList.DeleteFirst(p);
		 s->AddToShortestRdyList(p);
	 }
	 processescount = 0;
	 TotalCT = 0;
 }

 void FCFS::ControllingKillSignals(int timestep)
 {
	 if (KillSigFound)
	 {
		 KillSigFound = false;
	 }
	 else
	 {
		 SIGKILL* tempkillsig = nullptr;
		 KillingSignalsList.peek(tempkillsig);
		 if (tempkillsig)
		 {
			 if (tempkillsig->getTime() == timestep)
			 {
				 KillingSignalsList.dequeue(tempkillsig);
				 delete tempkillsig;
				 tempkillsig = NULL;
			 }
		 }
	 }
 }

 void FCFS::KillingSigTime(SIGKILL*& KillingSig,int TimeStep)
 {
	 SIGKILL* TempKillSig = nullptr;
	 KillingSignalsList.peek(TempKillSig);
	 if (TempKillSig)
	 {
		 if (TempKillSig->getTime() == TimeStep)
			 KillingSignalsList.dequeue(KillingSig);
		 else
			 KillingSig = nullptr;
	 }
	 else
		 KillingSig = nullptr;
 }

 bool FCFS::KillingSigAction(SIGKILL* KillingSig)
 {
	 if (KillingSig)
	 {
		 Process*KilledProcess=nullptr;
		 int Position=0;
		 if (RDYListIDs.Find(KillingSig->getID(), Position))
		 {
			 int id = 0;  //dummy integer
			 RDYList.DeleteNodeAtPosition(KilledProcess, Position);
			 RDYListIDs.DeleteNodeAtPosition(id, Position);
			 s->addToTrm(KilledProcess);
			 s->ChildrenKilling(KilledProcess); //Killing the orphans operation
			 processescount--;
			 s->IncrementKilledCount();
			 return true;
		 }
		 else
			 if (RUNNING)
			 {
				 if (KillingSig->getID() == *RUNNING)
				 {
					 s->addToTrm(RUNNING);
					 s->ChildrenKilling(RUNNING); //Killing the orphans operation
					 isbusy = false;
					 RUNNING = nullptr;
					 s->DecrementRunningCount();
					 s->IncrementKilledCount();
					 return true;
				 }
				 else
					 return false;
			 }
			 else
				 return false;
	 }
	 else
		 return false;
	
 }

 void FCFS::ReturnFirst(Process*&p)
 {
	 if (!RDYList.isEmpty())
	 {
		 RDYList.DeleteFirst(p);
		 RDYList.InsertBeg(p);
	 }
 }

 bool FCFS::NothingToExecute()
 {
	 return(!RUNNING && RDYList.isEmpty());
		
 }

//destructor
FCFS::~FCFS()
{
	
}

