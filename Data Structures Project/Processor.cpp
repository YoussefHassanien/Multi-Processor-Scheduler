#include "Processor.h"
#pragma once


//Constructor
Processor::Processor(Scheduler* Sptr)
{
	s=Sptr;
	isbusy = false;
	RUNNING = NULL;
	processescount = 0;
	TotalBT = 0;  
	TotalIT = 0; 
	PLoad = 0;
	PUtil = 0;
}

//gets the process in running state
Process* Processor::getRunning()
{
	return RUNNING;
}

void Processor::SetRunning(Process* proc)
{
	RUNNING = proc;
}

//sets the processor running state
void Processor::setisbusy(bool b)
{
	isbusy = b;
}

//gets the processor running state
bool Processor::getisbusy()
{
	return isbusy;
}

//Getter for the processes count in the ready list
int Processor::Getprocessescount()
{
	return processescount;
}

//Getter for the processor ID
int Processor::getID()
{
	return ID;
}

// Getter for the total time of the busy state duration of the processor 
int Processor::GetTotalBT()
{
	return TotalBT;
}

//Getter for the total time of the idle state duration of the processor
int Processor::GetTotalIT()
{
	return TotalIT;
}

// Getter for the Processor Load perecentage 
int Processor::GetPLoad()
{
	return PLoad;
}

// Getter for the Processor Utilization Percentage
int Processor::GetPUtil()
{
	return PUtil;
}

int Processor::GetTotalCT()
{
	return TotalCT;
}

int Processor::SumCT()
{
	int sum = 0;
	Process* p;
	for (int i = 0; i < processescount; i++)
	{
		deleteprocess(p);
		sum += p->GetCT();
		AddToRdy(p);
	}
	TotalCT = sum;
	return (TotalCT);
}

//Destructor
Processor::~Processor()
{
}

//Operator overloading
ostream& operator<<(ostream& output, Processor& p)
{

		output << "Processor " << p.getID() << " " << p.Get_Processor_Type() << ":" << p.GetRDYListCount() << " RDY: ";
		p.Print_List();


	return output;
}

