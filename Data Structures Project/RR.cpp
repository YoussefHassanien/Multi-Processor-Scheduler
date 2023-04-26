#include "RR.h"

RoundRobin::RoundRobin(Scheduler* Sptr,int id,int ts): Processor(Sptr)
{
	ID = id;
	Time_Slice = ts;
}

void RoundRobin::AddToRdy(Process* p)
{
	RDY_List.enqueue(p);
	processescount++;
}

void RoundRobin::deleteprocess(Process*& p)
{
	RDY_List.dequeue(p);
	processescount--;
}

//Schedueling algorithm
void RoundRobin::ScheduleAlgo()
{

	if (RDY_List.isEmpty() && !RUNNING)
		return;

	Process* tmp=nullptr;
	/*Process* temp = nullptr;
	RDY_List.peek(temp);*/

	//sets a process as running if the processor is idle
	if (!isbusy)
	{
		deleteprocess(tmp);
		RUNNING = tmp;
		isbusy = true;                             //Set the processor as busy
		s->incrementRunningCount();
		return;
	}
	else
	{
		stepscounter++;
		RUNNING->DecrementCT();
	}

	if  (stepscounter==Time_Slice)   //the current timestep is the Round Robin timeslice
	{
		RDY_List.enqueue(RUNNING);               //The process goes back to the beginning of the RDY list
		RUNNING = NULL;
		isbusy = false;                          //Set the processor as idle
		s->DecrementRunningCount();
		stepscounter = 0;
		return;
	}
	
	
}

//Picks a process randomly to terminate it
bool RoundRobin::RandomTermination(int id)
{
	return false;
}

//Prints ready list processes
void RoundRobin::Print_List()
{
	RDY_List.Print();
}

//Returns the processor type
string RoundRobin::Get_Processor_Type()
{
	return "[RR]";
}

//Returns the number of processes in the ready list
int RoundRobin::GetRDYListCount()
{
	return RDY_List.NodesCounter;
}

//destructor
RoundRobin::~RoundRobin()
{

}

