#ifndef PROCESSOR_H
#define PROCESSOR_H
class Scheduler;
class Process;
#pragma once
#include "LinkedList.h"
#include "PriorityQueue.h"
#include <iostream>
#include"Scheduler.h"
#include "Process.h"

	class Processor
	{
	protected:
		Process* RUNNING;    //the process in the running state
		bool isbusy; //indicator if there is a process in the running state (busy=1,idle=0)
		string Type; // stirng indicating the processor type
		int ID;      //needs initialization and incrementation 
		int processescount; //number of processes in the ready queue of the processor
		Scheduler* s;
		int TotalBT; //the total time of the busy state duration of the processor 
		int TotalIT; //the total time of the idle state duration of the processor
		int PLoad; //Processor Load perecentage 
		int PUtil; //Processor Utilization Percentage

	public:

		Processor(Scheduler* Sptr);                                //Constructor
		virtual void AddToRdy(Process* p) = 0;                     //Adds a process to the processor ready list
		virtual void deleteprocess(Process*& p) = 0;   //deletes a give process when it moves to another queue or to being blocked 
		virtual void ScheduleAlgo() = 0;                           //Schedueling algorithm
		void setisbusy(bool b);                                    //sets the processor running state
		Process* getRunning();                                     //gets the process in running state
		bool getisbusy();                                          //returns the processor's running state
		int Getprocessescount();                                   //Getter for the processes count in the ready list
		virtual bool RandomTermination(int id)=0;                  //Picks a process randomly to terminate it
		int getID();                                               //Getter for the processor ID
		virtual void Print_List() = 0;                             //Prints the ready list
		friend ostream& operator<<(ostream& output, Processor& p); //Operator overloading
		virtual string Get_Processor_Type() = 0;                   //Returns the processor type
		virtual int GetRDYListCount()=0;                           //Returns the number of ready lists
		int GetTotalBT();                   // Getter for the total time of the busy state duration of the processor 
		int GetTotalIT();                   //Getter for the total time of the idle state duration of the processor
		int GetPLoad();                     // Getter for the Processor Load perecentage 
		int GetPUtil();                     // Getter for the Processor Utilization Percentage
		~Processor();                       //Destructor

	};
#endif



