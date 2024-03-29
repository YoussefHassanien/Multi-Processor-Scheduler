#ifndef SJF_
#define SJF_

#pragma once
#include<iostream>
#include"Processor.h"
#include"Process.h"


class SJF :public Processor
{
private:
	PriorityQueue<Process*> RDY_List;   //list of the processes ready to be executed


public:

	
	SJF(Scheduler* Sptr,int id);       //constructor
	void AddToRdy(Process* p);         //Adds a process to the processor ready list
	void DeleteProcess(Process*& p);   //deletes a give process when it moves to another queue or to being blocked
	void ScheduleAlgo(int& timestep, int& stoptime, int rrcnt, int sjfcnt);   //Schedueling algorithm
	void Print_List();                 //Prints ready list processes
	string Get_Processor_Type();       //Returns the processor type
	int GetRDYListCount();             //Returns the number of processes in the ready list
	bool Search(Process* value);       //Searches for a specific process in the ready list
	void DeleteProcessAtPosition(Process*& p);      //deletes a process in any place in the RDYList
	bool NothingToExecute();                         //checks if the processor's running state and RDYList are empty
	void ReturnFirst(Process*& p);
	void EmptyProcessor();
	bool KillingSigAction(SIGKILL* KillingSig);
	~SJF();                            //Destructor
	
};






#endif 
