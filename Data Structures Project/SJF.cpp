
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
	Process* temp = nullptr;
	RDY_List.peek(temp);
	//sets a process as running if the processor is idle

	if (!isbusy && temp->GetAT() == s->getTimeStep())
	{
		return;
	}

	if (!isbusy && !RUNNING && temp->GetAT() < s->getTimeStep())
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
		s->addToTrm(RUNNING);                      //add to TRM list
		RUNNING = NULL;
		isbusy = false;                            //Set the processor as idle
		s->DecrementRunningCount();
		return;
	}
	else
	{
		//Generates a random number 
		int random = s->generaterandom(1,100);
		if (random >= 1 && random <= 15)
		{
			s->addtoblocklist(RUNNING);       //add to BLK list
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
			s->addToTrm(RUNNING);           //add to TRM list
			s->DecrementRunningCount();
			RUNNING = NULL;
			isbusy = false;                 //Set the processor as idle
		}
		else
			RUNNING->DecrementCT();

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




