#include "RR.h"

RoundRobin::RoundRobin(Scheduler* Sptr,int id,int ts, int rtf): Processor(Sptr),TimeSlice(ts),RTF(rtf)
{
	ID = id;
}

void RoundRobin::AddToRdy(Process* p)
{
	RDY_List.enqueue(p);
	processescount++;
	TotalCT = TotalCT + p->GetCT();
}

void RoundRobin::DeleteProcess(Process*& p)
{
	RDY_List.dequeue(p);
	processescount--;
	TotalCT = TotalCT - p->GetCT();
}

//Schedueling algorithm
void RoundRobin::ScheduleAlgo(int& TimeStep, int& stoptime)
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

	if (RDY_List.isEmpty() && !RUNNING) //if there is nothing in the ready list and no running process
	{
		TotalIT++;
		return;
	}
	else
		TotalBT++;

	//sets a process as running if the processor is idle
	if (!isbusy && !RDY_List.isEmpty())
	{
		RRtoSJF_Migration();
		RDY_List.dequeue(TempProcess);
		if (TempProcess)
		{
			processescount--;
			RUNNING = TempProcess;
			TempProcess->SetRT(TimeStep);
			isbusy = true;                 //Set the processor as busy
			s->incrementRunningCount();
		}
			return;
	}
	else if (isbusy && RUNNING->GetCT()) //Same as if RUNNING->GetCT!=0
	{
		RUNNING->DecrementCT();
		RUNNING->IncrementRunningFor();
		if (RUNNING->GetN())	   /* the condition is same as if RUNNING->GetN()!=0 ,
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
				else  if (!((TimeStep-1) % TimeSlice))   //the current timestep is the Round Robin timeslice
				{
					RDY_List.enqueue(RUNNING);               //The process goes back to the beginning of the RDY list
					processescount++;
					RUNNING = nullptr;
					isbusy = false;                          //Set the processor as idle
					s->DecrementRunningCount();
				}
			}
			else if (!((TimeStep - 1) % TimeSlice))   //the current timestep is the Round Robin timeslice
			{
				RDY_List.enqueue(RUNNING);               //The process goes back to the beginning of the RDY list
				processescount++;
				RUNNING = nullptr;
				isbusy = false;                          //Set the processor as idle
				s->DecrementRunningCount();
			}
		}
		else if (!((TimeStep - 1) % TimeSlice))   //the current timestep is the Round Robin timeslice
		{
			RDY_List.enqueue(RUNNING);               //The process goes back to the beginning of the RDY list
			processescount++;
			RUNNING = nullptr;
			isbusy = false;                          //Set the processor as idle
			s->DecrementRunningCount();
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

//Controls the process migration from RR processor to SJF processor
void RoundRobin::RRtoSJF_Migration()
{  
	Process* p;
	while (RDY_List.peek(p) && !p->GetParent() && p->GetCT() < RTF)
	{
		RDY_List.dequeue(p);
		processescount--;
		s->FromRRtoShortestSJF(p);
		s->IncrementRTF();
	}
	
}

bool RoundRobin::Search(Process* value)
{
	return RDY_List.Find(value);
}



void RoundRobin::DeleteProcessAtPosition(Process*& p)
{
	return;
}

void RoundRobin::ReturnFirst(Process*& p)
{
	RDY_List.peek(p);
}


void RoundRobin::EmptyProcessor()
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
RoundRobin::~RoundRobin()
{

}

