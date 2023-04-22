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
	void deleteprocess(Process*& p);   //deletes a give process when it moves to another queue or to being blocked
	void ScheduleAlgo();               //Schedueling algorithm
	bool RandomTermination(int id);    //Picks a process randomly to terminate it
	void Print_List();                 //Prints ready list processes
	string Get_Processor_Type();       //Returns the processor type
	int GetRDYListCount();             //Returns the number of processes in the ready list
	~SJF();                            //Destructor
	
};






#endif 
