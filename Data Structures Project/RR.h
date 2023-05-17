#pragma once
#include "CyclicQueue.h"
#include "Processor.h"
class RoundRobin :public Processor
{
private:
	LinkedQueue<Process*> RDY_List;                 //RDY list
	const int TimeSlice, RTF;					    //time slice

public:
	RoundRobin(Scheduler* Sptr,int id,int ts, int rtf);      //constructor
	void AddToRdy(Process* p);                      //Adds a process to the processor ready list
	void DeleteProcess(Process*& p);                //deletes a give process when it moves to another queue or to being blocked
	void ScheduleAlgo(int& timestep, int& stoptime);                //Schedueling algorithm
	void Print_List();                              //Prints ready list processes
	string Get_Processor_Type();                    //Returns the processor type 
	int GetRDYListCount();                          //Returns the number of processes in the ready list
	void RRtoSJF_Migration();                       //Controls the process migration from RR processor to SJF processor
	bool Search(Process* value);                    //Searches for a specific process in the ready list
	bool NothingToExecute();                         //checks if the processor's running state and RDYList are empty
	void DeleteProcessAtPosition(Process*& p);      //deletes a process in any place in the RDYList
	void ReturnFirst(Process*& p);
	void EmptyProcessor();
	bool KillingSigAction(SIGKILL* KillingSig);
	~RoundRobin();                                  //Destructor

};


