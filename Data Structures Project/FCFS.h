#pragma once
#include "Processor.h"
#include "LinkedQueue.h"
#include "LinkedList.h"
#include "SigKill.h"

class FCFS : public Processor
{
private:
	LinkedList<Process*> RDYList;                   //RDY list
	LinkedList<int> RDYListIDs;                     //list of ID of processes in the RDY list
	static LinkedQueue<SIGKILL*> KillingSignalsList; //A Queue of killing signals pointers 
public:
	FCFS(Scheduler* Sptr,int id=0);                 //constructor
	void AddToRdy(Process* p);                      //Adds a process to the processor ready list
	void DeleteProcess(Process*& p);                //deletes a give process when it moves to another queue or to being blocked
	void ScheduleAlgo();                            //Schedueling algorithm
	bool RandomTermination(int id);                 //Picks a process randomly to terminate it
	void deleteprocessid(Process* p);               //Deletes a process ID from RDYListIDs
	void AddToRdyIDs(Process* p);                   //Adds a process ID to RDYListIDs
	void DeleteChild(Process* p);                   //Deletes a child process from the ready list
	void Print_List();                              //Prints ready list processes
	string Get_Processor_Type();                    //Returns the processor type
	int GetRDYListCount();                          //Returns the number of processes in the ready list
	void FCFStoRR_Migration();                      //Controls the process migration from FCFS processor to RR processor
	bool Search(Process* value);                    //Searches for a specific process in the ready list
	int SumCT();                                    //Sums the CT of all processes in the ready queue
	static void AddKillingSignal(SIGKILL*killsignal);   //enqueue a killing in the Killing Signals List
	~FCFS();                                        //Destructor
	         
};

