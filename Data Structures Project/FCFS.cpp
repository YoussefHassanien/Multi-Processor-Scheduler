#include "FCFS.h"

//Constructor
FCFS::FCFS(Scheduler*Sptr,int id,int prob): Processor(Sptr)
{
	ID = id;
	Fork_Prob = prob;
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
void FCFS::deleteprocess(Process*& p)
{
	RDYList.DeleteFirst(p);
	processescount--;
	deleteprocessid(p);
}

//Deletes a process ID from RDYListIDs
void FCFS::deleteprocessid(Process* p)
{
	int y;
	RDYListIDs.DeleteFirst(y);
}




//Deletes a child process from the ready list
void FCFS::DeleteChild(Process* p)
{
	RDYList.DeleteNode(p);
	RDYListIDs.DeleteNode(p->GetID());
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
	Process* RDYPeek = nullptr;

	RDYList.peek(RDYPeek);

	if (RDYList.isEmpty() && !RUNNING) // if there is nothing in the ready list and no process is running
		return;


	if (!isbusy) //sets a process as running if the processor is idle
	{
		deleteprocess(tmp);
		RUNNING = tmp;
		isbusy = true;                                  //Set the processor as busy
		s->incrementRunningCount();
		return;
	}
	else if (isbusy && RUNNING->GetCT() != 0) 
	{
		RUNNING->DecrementCT();
		RUNNING->IncrementRunningFor();
	}

}


//destructor
FCFS::~FCFS()
{
	
}

