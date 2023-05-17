#pragma once
#include "Processor.h"
#include "LinkedQueue.h"
#include "LinkedList.h"
#include "SigKill.h"

class FCFS : public Processor
{
private:
	LinkedList<Process*> RDYList;                    //RDY list
	LinkedList<int> RDYListIDs;                      //list of ID of processes in the RDY list
	static LinkedQueue<SIGKILL*> KillingSignalsList; //A Queue of killing signals pointers 
	const int ForkProb;                              //Forking probability 
public:
	FCFS(Scheduler* Sptr,int forkprob, int id = 0); //constructor
	void AddToRdy(Process* p) override;             //Adds a process to the processor ready list
	void DeleteProcess(Process*& p);                //deletes a give process when it moves to another queue or to being blocked
	void DeleteProcessAtPosition(Process*& p);      //deletes a process in any place in the RDYList
	void ScheduleAlgo(int &timestep, int& stoptime);         //Schedueling algorithm
	void DeleteProcessID(Process* p);                //Deletes a process ID from RDYListIDs
	void AddToRdyIDs(Process* p);                    //Adds a process ID to RDYListIDs
	void Print_List();                               //Prints ready list processes
	string Get_Processor_Type();                     //Returns the processor type
	int GetRDYListCount();                           //Returns the number of processes in the ready list
	void FCFStoRR_Migration(int timestep);           //Controls the process migration from FCFS processor to RR processor
	bool Search(Process* value);                     //Searches for a specific process in the ready list
	void ReturnFirst(Process*& p);
	bool NothingToExecute();                         //checks if the processor's running state and RDYList are empty
	static void AddKillingSignal(SIGKILL*killsignal);//enqueue a killing in the Killing Signals List
	void EmptyProcessor();
	void KillingSigTime(SIGKILL*&KillingSig,int TimeStep); //Checks if the current timestep is the one which we should do the Killing Signal
	bool KillingSigAction(SIGKILL* KillingSig);            //The Action of Killing itself 
	~FCFS();                                               //Destructor 
};

