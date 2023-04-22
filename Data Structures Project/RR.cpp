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
	//sets a process as running if the processor is idle
	if (!isbusy)
	{

		deleteprocess(tmp);
		RUNNING = tmp;
		isbusy = true;                             //Set the processor as busy
		s->incrementRunningCount();
		return;
	}

	//if the process's CPU time is over
	if (RUNNING->GetCT() == 0)
	{
		s->addToTrm(RUNNING);                     //add to TRM list
		RUNNING = NULL;
		isbusy = false;                          //Set the processor as idle
		s->DecrementRunningCount();
		return;
	}
	else if  (s->getTimeStep() % Time_Slice == 0)   //the current timestep is the Round Robin timeslice
	{

		RDY_List.enqueue(RUNNING);               //The process goes back to the beginning of the RDY list
		RUNNING = NULL;
		isbusy = false;                          //Set the processor as idle
		s->DecrementRunningCount();
		return;
	}
	else 
	{
		int random = s->generaterandom(1,100);
		if (random >= 1 && random <= 15)
		{
			s->addtoblocklist(RUNNING);        //add to BLK list
			s->DecrementRunningCount();
			RUNNING = NULL;
			isbusy = false;                    //Set the processor as idle
		}
		else if (random >= 20 && random <= 30)
		{
			AddToRdy(RUNNING);               //add to RDY list
			s->DecrementRunningCount();
			RUNNING = NULL;
			isbusy = false;                  //Set the processor as idle
		}
		else if (random >= 50 && random <= 60)
		{ 
			s->addToTrm(RUNNING);              //add to TRM list
			s->DecrementRunningCount();
			RUNNING = NULL;
			isbusy = false;                     //Set the processor as idle
		}
		else
			RUNNING->DecrementCT();
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

