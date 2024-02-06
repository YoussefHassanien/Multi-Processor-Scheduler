#include "Processor.h"
#pragma once


//Constructor
Processor::Processor(Scheduler* Sptr)
{
	s=Sptr;
	isbusy = false;
	isoverheating = false;
	RUNNING = nullptr;
	processescount = 0;
	TotalBT = 0;		
	TotalIT = 0;		
	PLoad = 0;			
	PUtil = 0;			
	TotalCT = 0;		
	StoppedFor = 0;
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
float Processor::GetPLoad(int TotalTRT)
{
	return (float)TotalBT/TotalTRT;
}

// Getter for the Processor Utilization Percentage
void Processor::GetPUtil(float& PUtil)
{
	PUtil= (float)TotalBT/(TotalBT+TotalIT);
}

int Processor::GetTotalCT()
{
	return TotalCT;
}




void Processor::setOverHeating(bool b)
{
	isoverheating = b;
	if (b == true)
	{
		if (!NothingToExecute())
			EmptyProcessor();
		else
			isoverheating = false;
	}
}

bool Processor::getOverHeating()
{
	return isoverheating;
}

//Destructor
Processor::~Processor()
{
}

//Operator overloading
ostream& operator<<(ostream& output, Processor& p)
{
	if (p.getOverHeating())
	{
		output << "Processor " << p.getID() << " " << p.Get_Processor_Type() << "[OVER_HEATING]" << ":" << p.GetRDYListCount() << " RDY: ";
		p.Print_List();
	}
	else
	{
		output << "Processor " << p.getID() << " " << p.Get_Processor_Type() <<  ":" << p.GetRDYListCount() << " RDY: ";
		p.Print_List();
	}


	return output;
}

