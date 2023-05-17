
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
	TotalCT = TotalCT + p->GetCT();
	processescount++;
}

//deletes a given process when it moves to another queue or to being blocked
void SJF::DeleteProcess(Process*& p)
{
	RDY_List.dequeue(p);
	TotalCT = TotalCT - p->GetCT();
	processescount--;
}

//Schedueling algorithm
void SJF::ScheduleAlgo(int &TimeStep, int& stoptime)
{
	IO* TempIO = nullptr;
	Process* TempProcess = nullptr;
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
	if (RDY_List.isEmpty())
		TotalCT = 0;

	if (NothingToExecute()) //if there is nothing in the ready list and no running process
	{
		TotalIT++;
		return;
	}
	else
		TotalBT++;
	
	//sets a process as running if the processor is idle
	if (!isbusy && !RUNNING)
	{
		
		RDY_List.dequeue(TempProcess);
		processescount--;
		RUNNING = TempProcess;
		TempProcess->SetRT(TimeStep);
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
		s->ChildrenKilling(RUNNING);
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



void SJF::DeleteProcessAtPosition(Process*& p)
{
	return;
}

bool SJF::NothingToExecute()
{
	return(!RUNNING && RDY_List.isEmpty());
}

void SJF::ReturnFirst(Process*& p)
{
	RDY_List.peek(p);
}
void SJF::EmptyProcessor()
{
	if (RUNNING)
	{
		s->AddToShortestRdyList(RUNNING);
		RUNNING = NULL;
		isbusy = false;
		s->DecrementRunningCount();
	}
	while (!RDY_List.isEmpty())
	{
		Process* p = nullptr;
		RDY_List.dequeue(p);
		s->AddToShortestRdyList(p);
	}
	processescount = 0;
	TotalCT = 0;
}
//destructor
SJF::~SJF()
{

}




