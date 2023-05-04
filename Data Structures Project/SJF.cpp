
#include "SJF.h"


//constructor
SJF::SJF(Scheduler* Sptr,int id) : Processor(Sptr)
{
	ID =id;
}

//Adds a process to the processor ready list
void SJF::AddToRdy(Process* p)
{
	RDY_List.enqueue(p, p->GetCT());
	processescount++;
}

//deletes a give process when it moves to another queue or to being blocked
void SJF::deleteprocess(Process*& p)
{
	RDY_List.dequeue(p);
	processescount--;
}

//Schedueling algorithm
void SJF:: ScheduleAlgo()

{
	
	if (RDY_List.isEmpty())
		return;
	Process* tmp=nullptr;
	/*Process* temp = nullptr;
	RDY_List.peek(temp);*/
	

	//sets a process as running if the processor is idle
	if (!isbusy && !RUNNING)
	{
		deleteprocess(tmp);
		RUNNING = tmp;
		isbusy = true;                             //Set the processor as busy
		s->incrementRunningCount();
		return;
	}

	else if (isbusy) 
	{
		RUNNING->DecrementCT();
		RUNNING->IncrementRunningFor();
	}


}

//Picks a process randomly to terminate it
bool SJF::RandomTermination(int id)
{
	return false;
}

//Prints ready list processes
void SJF::Print_List()
{
	RDY_List.Print();
}

//Returns the processor type
string SJF::Get_Processor_Type()
{
	return "[SJF]";
}

//Returns the number of processes in the ready list
int SJF::GetRDYListCount()
{
	return RDY_List.NodesCounter;
}

//destructor
SJF::~SJF()
{

}




