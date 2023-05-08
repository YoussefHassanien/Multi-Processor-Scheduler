#pragma once
#include "CyclicQueue.h"
#include "Processor.h"
class RoundRobin :public Processor
{
private:
	LinkedQueue<Process*> RDY_List;                 //RDY list
	int Time_Slice;                                 //time slice
	int stepscounter = 0;

public:
	RoundRobin(Scheduler* Sptr,int id,int ts);      //constructor
	void AddToRdy(Process* p);                      //Adds a process to the processor ready list
	void DeleteProcess(Process*& p);                //deletes a give process when it moves to another queue or to being blocked
	void ScheduleAlgo();                            //Schedueling algorithm
	bool RandomTermination(int id);                 //Picks a process randomly to terminate it
	void Print_List();                              //Prints ready list processes
	string Get_Processor_Type();                    //Returns the processor type 
	int GetRDYListCount();                          //Returns the number of processes in the ready list
	void RRtoSJF_Migration();                       //Controls the process migration from RR processor to SJF processor
	bool Search(Process* value);                    //Searches for a specific process in the ready list
	int SumCT();                                    //Sums the CT of all processes in the ready queue
	~RoundRobin();                                  //Destructor

};


