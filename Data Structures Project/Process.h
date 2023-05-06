#pragma once
#include<iostream>
#include"IO.h"
#include "Scheduler.h"
#include"BinaryTree.h"
#include"LinkedQueue.h"
using namespace std;
class Scheduler;
class Process
{
private:
	int ID // Process ID 
		, AT // Arrival Time
		, RT // Response Time 
		, CT //CPU Time
		, TT // Termination Time
		, TRT // Turnaround Duration
		, WT // Waiting Time
		, N // Number of Times the process requests I/O
		, RunningFor //How long the process has been running so far
		;
	Scheduler* s;
	LinkedQueue<IO*>* IOqueue; //IOs Queue for each process
	Process* Parent;   //a pointer to the parent process that have created the forked processes 
	Process* FirstChild; //a pointer to the first forked child
	Process* SecondChild; //a pointer to the second forked child
	bool Orph;
	enum State
	{
		New,
		Rdy, 
		Run,
		Blck,
		Term

	};
	State S;
public:

	Process(int at = 0, int id = 0, int ct = 0, int n = 0);          //Constructor
	void SetID(int id);                                              //Setter for the process ID 
	void SetAT(int at);                                              //Setter for the Arrival Time
	void SetRT(int CPU_First_AT);                                    //Setter for the Arrival Time
	void SetCT(int ct);                                              //Setter for the CPU time
	void SetTT(int tt);                                              //Setter for the Termination time
	void SetTRT(int trt);                                            //Setter for the Turnarround time
	void SetWT(int wt);                                              //Setter for the Wait Time
	void SetN(int n);                                                //Setter for the Number of IOs
	void SetOrph(bool orph);                                         //Setter for the orphan
	void SetS(int s);                                                //Setter for the Process State
	int GetID();                                                     //Getter for the process ID 
	int GetAT();                                                     //Getter for the Arrival Time
	int GetRT();                                                     //Getter for the Arrival Time
	int GetCT();                                                     //Getter for the CPU time
	int GetTT();                                                     //Getter for the Termination time
	int GetTRT();                                                    //Getter for the Turnarround time
	int GetWT();                                                     //Getter for the Wait Time
	int GetN();                                                      //Getter for the number of IOs
	bool GetOrph();                                                  //Getter for the orphan
	int GetRunningFor();                                             //Getter for how long the process has been running so far
	void GetFirstIO(IO*& ioTemp);                                    //Getter for the front IO in the IOs queue
	bool CheckIO_D();
	void AddChildren(Process*child1,Process*child2=nullptr);         //Add 2 Childs to the Childs Tree
	void AddIO(LinkedQueue<IO*>* ioq);                               //Getter for the Orphan boolean
	void PrintProcessInfo();                                         //Prints the Processes info
	void DecrementCT();                                              //decrements the CT by one 
	void IncrementRunningFor();                                      //Increments RunningFor by one 
	int WTsofar();                                                   //Calculates the WT so far
	friend ostream& operator<<(ostream& output,Process &p);          //<< Operator overloading
    friend bool operator ==(Process& p1,Process& p2);                //== Operator Overloading 
	friend bool operator==(int value,Process& p);                    //== Operator Overloading when the Process ID is sent instead of 2 Processes
	~Process();                                                      //Destructor
};

