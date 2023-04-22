#pragma once
#include "Processor.h"
#include "LinkedQueue.h"
#include "LinkedList.h"

class FCFS : public Processor
{
private:
	LinkedList<Process*> RDYList;                   //RDY list
	LinkedList<int> RDYListIDs;                     //list of ID of processes in the RDY list
	LinkedList<Process*>FamilyList;                 // a list of pointers to the parent and its children and grandchildren
	int Fork_Prob;

public:
	FCFS(Scheduler* Sptr,int id=0,int prob=0);      //constructor
	void AddToRdy(Process* p);                      //Adds a process to the processor ready list
	void deleteprocess(Process*& p);                //deletes a give process when it moves to another queue or to being blocked
	void ScheduleAlgo();                            //Schedueling algorithm
	bool RandomTermination(int id);                 //Picks a process randomly to terminate it
	void deleteprocessid(Process* p);               //Deletes a process ID from RDYListIDs
	void AddToRdyIDs(Process* p);                   //Adds a process ID to RDYListIDs
	void DeleteChild(Process* p);                   //Deletes a child process from the ready list
	void Print_List();                              //Prints ready list processes
	string Get_Processor_Type();                    //Returns the processor type
	int GetRDYListCount();                          //Returns the number of processes in the ready list
	~FCFS();                                        //Destructor
	         
};

