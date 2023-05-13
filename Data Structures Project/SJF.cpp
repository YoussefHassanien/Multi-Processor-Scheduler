
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

//deletes a given process when it moves to another queue or to being blocked
void SJF::DeleteProcess(Process*& p)
{
	RDY_List.dequeue(p);
	processescount--;
}

//Schedueling algorithm
void SJF::ScheduleAlgo(int TimeStep)
{
	IO* TempIO = nullptr;
	Process* TempProcess = nullptr;
	if (RDY_List.isEmpty() && !RUNNING)
		return;
	
	//sets a process as running if the processor is idle
	if (!isbusy && !RUNNING)
	{
		RDY_List.dequeue(TempProcess);
		processescount--;
		RUNNING = TempProcess;
		TempProcess->SetRT(TimeStep - TempProcess->GetAT());
		isbusy = true;                             //Set the processor as busy
		s->incrementRunningCount();
		return;
	}

	else if (isbusy && RUNNING->GetCT()) //Same as if RUNNING->GetCT!=0
	{
		RUNNING->DecrementCT();
		RUNNING->IncrementRunningFor();
		if (RUNNING->GetN())		/* the condition is same as if RUNNING->GetN()!=0 , 
				                    decrements the IO_R while the process is running */ 
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
		s->addToTrm(RUNNING);
		s->ParentKilling(RUNNING);
		isbusy = false;
		RUNNING = nullptr;
		s->DecrementRunningCount();
	}


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

bool SJF::Search(Process* value)
{
	return RDY_List.Find(value);
}

int SJF::SumCT()
{
	Process* p;
	PriorityQueue<Process*>TempRDYList;
	for (int i = 0; i < processescount; i++)
	{
		RDY_List.dequeue(p);
		TotalCT = TotalCT + p->GetCT();
		TempRDYList.enqueue(p,p->GetCT());
	}
	for (int i = 0; i < processescount; i++)
	{
		TempRDYList.dequeue(p);
		RDY_List.enqueue(p, p->GetCT());
	}
	return TotalCT;
}

void SJF::DeleteProcessAtPosition(Process*& p)
{
	return;
}

//destructor
SJF::~SJF()
{

}




