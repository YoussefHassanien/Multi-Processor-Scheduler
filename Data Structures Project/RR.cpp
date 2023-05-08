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
	IO* ioTemp;

	if (RDY_List.isEmpty() && !RUNNING)
		return;

	Process* tmp=nullptr;
	/*Process* temp = nullptr;
	RDY_List.peek(temp);*/

	//sets a process as running if the processor is idle
	if (!isbusy)
	{
		DeleteProcess(tmp);
		RUNNING = tmp;
		tmp->SetRT(s->getTimeStep() - tmp->GetAT());
		isbusy = true;                             //Set the processor as busy
		s->incrementRunningCount();
		return;
	}
	else
	{
		stepscounter++;
		RUNNING->DecrementCT();
		RUNNING->IncrementRunningFor();
		if (RUNNING->GetN() != 0)						// decrements the IO_R while the process is running 
		{
			RUNNING->GetFirstIO(ioTemp);
			if (ioTemp)
			{
				if (ioTemp->GetRequest() >= 0)
				{
					ioTemp->DecrementIO_R();
				}


				if (ioTemp->GetRequest() == -1)
				{
					s->addtoblocklist(RUNNING);
					isbusy = false;
					RUNNING = nullptr;
					s->DecrementRunningCount();
				}
			}
		}
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

	if (isbusy && RUNNING->GetCT() == 0)
	{
		s->addToTrm(RUNNING);
		isbusy = false;
		RUNNING = nullptr;
		s->DecrementRunningCount();
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

//Controls the process migration from RR processor to SJF processor
void RoundRobin::RRtoSJF_Migration()
{  
	if (RUNNING)   //there is a running process to check the migration condition
	{
		Process* p = nullptr;
		Process* newrunning = nullptr;
		if (RUNNING->GetCT() < s->GetRTF())
		{
			p = RUNNING;
			RDY_List.dequeue(newrunning);
			RUNNING = newrunning;
			s->FromRRtoShortestSJF(p);
			RRtoSJF_Migration();
		}
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

//destructor
RoundRobin::~RoundRobin()
{

}

