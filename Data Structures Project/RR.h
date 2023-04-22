#pragma once
#include "CyclicQueue.h"
#include "Processor.h"
class RoundRobin :public Processor
{
private:
	CyclicQueue<Process*> RDY_List;                 //RDY list
	int Time_Slice;                                 //time slice
	

public:
	RoundRobin(Scheduler* Sptr,int id,int ts);      //constructor
	void AddToRdy(Process* p);                      //Adds a process to the processor ready list
	void deleteprocess(Process*& p);                //deletes a give process when it moves to another queue or to being blocked
	void ScheduleAlgo();                            //Schedueling algorithm
	bool RandomTermination(int id);                 //Picks a process randomly to terminate it
	void Print_List();                              //Prints ready list processes
	string Get_Processor_Type();                    //Returns the processor type 
	int GetRDYListCount();                          //Returns the number of processes in the ready list
	~RoundRobin();                                  //Destructor

};


