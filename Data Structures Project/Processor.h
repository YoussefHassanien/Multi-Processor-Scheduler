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
		string Type; //stirng indicating the processor type
		int ID;      //needs initialization and incrementation 
		int processescount; //number of processes in the ready queue of the processor
		Scheduler* s;
		int TotalBT; //the total time of the busy state duration of the processor 
		int TotalIT; //the total time of the idle state duration of the processor
		int PLoad; //Processor Load perecentage 
		int PUtil; //Processor Utilization Percentage
		int TotalCT; //Sum of the CT of all processes in the ready list
		bool isoverheating;
		int StoppedFor;      //indicator of how much time the processor have been in stop mode

	public:

		Processor(Scheduler* Sptr);                                //Constructor
		virtual void AddToRdy(Process* p) = 0;                     //Adds a process to the processor ready list
		virtual void DeleteProcess(Process*& p) = 0;               //deletes a given process when it moves to another queue or to being blocked 
		virtual bool Search(Process* value) = 0;                   //Searches for a specific process in the processors ready lists
		virtual void ScheduleAlgo(int& x, int& stoptime) = 0;                           //Schedueling algorithm
		void setisbusy(bool b);                                    //sets the processor running state
		Process* getRunning();                                     //gets the process in running state
		void SetRunning(Process* proc);
		virtual void DeleteProcessAtPosition(Process*& p)=0;       //deletes a process in any place in the RDYList (Applicable only for FCFS)
		bool getisbusy();                                          //returns the processor's running state
		int Getprocessescount();                                   //Getter for the processes count in the ready list
		int getID();                                               //Getter for the processor ID
		virtual void Print_List() = 0;                             //Prints the ready list
		friend ostream& operator<<(ostream& output, Processor& p); //Operator overloading
		virtual string Get_Processor_Type() = 0;                   //Returns the processor type
		virtual int GetRDYListCount()=0;                           //Returns the number of ready lists
		int GetTotalBT();                   // Getter for the total time of the busy state duration of the processor 
		int GetTotalIT();                   //Getter for the total time of the idle state duration of the processor
		float GetPLoad(int TotalTRT);                     // Getter for the Processor Load perecentage 
		void GetPUtil(float& PUtil);                     // Getter for the Processor Utilization Percentage
		int GetTotalCT();                   //Getter for the total CT of all processes in the ready list
		virtual int SumCT()=0;              //Sums the CT of all processes in the ready queue
		virtual void ReturnFirst(Process *&p) = 0;		//Return the first process in each processor's ready list
		virtual void EmptyProcessor() = 0;             // Emties the running process and the rdylist
		void setOverHeating(bool b);                  // setter for overheating state
		bool getOverHeating();                        //getter for overheating state
		~Processor();                       //Destructor
	};
#endif



