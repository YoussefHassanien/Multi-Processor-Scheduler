#include "EDF.h"

EDF::EDF(Scheduler* Sptr, int id):Processor(Sptr)
{
	ID = id;
}

void EDF::AddToRdy(Process* p)
{
	if (RUNNING)
	{
		if (p->GetDeadline() < RUNNING->GetDeadline())
		{
			RDY_List.enqueue(RUNNING, RUNNING->GetDeadline());
			TotalCT = TotalCT + RUNNING->GetCT();
			processescount++;
			RUNNING = p;
		}
		else
		{
			RDY_List.enqueue(p, p->GetDeadline());
			TotalCT = TotalCT + p->GetCT();
			processescount++;
		}
	}
	else
	{
		RDY_List.enqueue(p, p->GetDeadline());
		TotalCT = TotalCT + p->GetCT();
		processescount++;
	}	
}

void EDF::DeleteProcess(Process*& p)
{
	RDY_List.dequeue(p);
	TotalCT = TotalCT - p->GetCT();
	processescount--;
}

void EDF::ScheduleAlgo(int& timestep, int& stoptime, int rrcnt, int sjfcnt)
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
		TempProcess->SetRT(timestep);
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

void EDF::Print_List()
{
	RDY_List.Print();
}

string EDF::Get_Processor_Type()
{
	return "[EDF]";
}

int EDF::GetRDYListCount()
{
	return RDY_List.NodesCounter;
}

bool EDF::Search(Process* value)
{
	return RDY_List.Find(value);
}



void EDF::DeleteProcessAtPosition(Process*& p)
{
	return;
}

bool EDF::NothingToExecute()
{
	return(!RUNNING && RDY_List.isEmpty());
}

void EDF::EmptyProcessor()
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

void EDF::ReturnFirst(Process*& p)
{
	RDY_List.peek(p);
}

bool EDF::KillingSigAction(SIGKILL* KillingSig)
{
	return false;
}

EDF::~EDF()
{
}
