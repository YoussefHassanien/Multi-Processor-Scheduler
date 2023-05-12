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

void RoundRobin::DeleteProcess(Process*& p)
{
	RDY_List.dequeue(p);
	processescount--;
}

//Schedueling algorithm
void RoundRobin::ScheduleAlgo()
{
	IO* TempIO = nullptr;
	Process* TempProcess = nullptr;
	if (RDY_List.isEmpty() && !RUNNING)
		return;

	//sets a process as running if the processor is idle
	if (!isbusy && (!RDY_List.isEmpty()))
	{
		RDY_List.dequeue(TempProcess);
		processescount--;
		RUNNING = TempProcess;
		TempProcess->SetRT(s->getTimeStep() - TempProcess->GetAT());
		isbusy = true;                             //Set the processor as busy
		s->incrementRunningCount();
		return;
	}
	else if (isbusy && RUNNING->GetCT() != 0)
	{
		RUNNING->DecrementCT();
		RUNNING->IncrementRunningFor();
		if (RUNNING->GetN() != 0)						// decrements the IO_R while the process is running 
		{
			RUNNING->GetFirstIO(TempIO);
			if (TempIO !=nullptr)
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
				else  if (s->CheckTimeSlice())   //the current timestep is the Round Robin timeslice
				{
					RDY_List.enqueue(RUNNING);               //The process goes back to the beginning of the RDY list
					RUNNING = NULL;
					isbusy = false;                          //Set the processor as idle
					s->DecrementRunningCount();
				}


			}
		}
		else if (s->CheckTimeSlice())   //the current timestep is the Round Robin timeslice
		{
			RDY_List.enqueue(RUNNING);               //The process goes back to the beginning of the RDY list
			RUNNING = NULL;
			isbusy = false;                          //Set the processor as idle
			s->DecrementRunningCount();
		}
	}
	else if (isbusy && RUNNING->GetCT() == 0)
	{
		s->addToTrm(RUNNING);
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
	RDY_List.peek(p);
	if (p->GetCT() < s->GetRTF())
	{
		RDY_List.dequeue(p);
		s->FromRRtoShortestSJF(p);
		RRtoSJF_Migration();
	}
}

bool RoundRobin::Search(Process* value)
{
	return RDY_List.Find(value);
}

int RoundRobin::SumCT()
{
	Process* p;
	for (int i = 0; i < processescount; i++)
	{
		RDY_List.IterativePeek(p, i + 1);
		TotalCT += p->GetCT();
	}
	return (TotalCT);
}

void RoundRobin::DeleteProcessAtPosition(Process*& p)
{
	return;
}

//destructor
RoundRobin::~RoundRobin()
{

}

