#pragma once
#ifndef EDF_
#define EDF_

#pragma once
#include<iostream>
#include"Processor.h"
#include"Process.h"


class EDF :public Processor
{
private:
	PriorityQueue<Process*> RDY_List;   //list of the processes ready to be executed


public:


	EDF(Scheduler* Sptr, int id);       //constructor
	void AddToRdy(Process* p);         //Adds a process to the processor ready list
	void DeleteProcess(Process*& p);   //deletes a give process when it moves to another queue or to being blocked
	void ScheduleAlgo(int& timestep, int& stoptime);   //Schedueling algorithm
	void Print_List();                 //Prints ready list processes
	string Get_Processor_Type();       //Returns the processor type
	int GetRDYListCount();             //Returns the number of processes in the ready list
	bool Search(Process* value);       //Searches for a specific process in the ready list
	void DeleteProcessAtPosition(Process*& p);      //deletes a process in any place in the RDYList
	bool NothingToExecute();                         //checks if the processor's running state and RDYList are empty
	void EmptyProcessor();
	void ReturnFirst(Process*& p);
	bool KillingSigAction(SIGKILL* KillingSig);
	~EDF();                            //Destructor

};






#endif 
