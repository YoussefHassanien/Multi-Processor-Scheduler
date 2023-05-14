#pragma once
#include<iostream>
#include"IO.h"
#include "Scheduler.h"
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
		, Actual_CT //original ct
		, IO_D //total IO Duration
		, IO_R  //IO Request time
		, Deadline //deadline of process
		;
	LinkedQueue<IO*> IOqueue; //IOs Queue for each process
	Process* Parent;   //a pointer to the parent process that have created this forked processes if it is a forked one
	Process* FirstChild; //a pointer to the first forked child
	Process* SecondChild; //a pointer to the second forked child

public:

	Process(int at = 0, int id = 0, int ct = 0, int deadline=0, int n = 0);          //Constructor
	void SetID(int id);                                              //Setter for the process ID 
	void SetAT(int at);                                              //Setter for the Arrival Time
	void SetRT(int CPU_First_AT);                                    //Setter for the Arrival Time
	void SetCT(int ct);                                              //Setter for the CPU time
	void SetTT(int tt);                                              //Setter for the Termination time
	void SetTRT(int trt);                                            //Setter for the Turnarround time
	void SetWT(int wt);                                              //Setter for the Wait Time
	void SetN(int n);                                                //Setter for the Number of IOs
	void SetDeadline(int dead);										 //Setter for the process deadline
	void SetParent(Process* parent);                                 //Setter for the parent
	int GetDeadline();											     //Getter for the Process Deadline
	int GetID();                                                     //Getter for the process ID 
	int GetAT();                                                     //Getter for the Arrival Time
	int GetRT();                                                     //Getter for the Arrival Time
	int GetCT();                                                     //Getter for the CPU time
	int GetTT();                                                     //Getter for the Termination time
	int GetTRT();                                                    //Getter for the Turnarround time
	int GetWT();                                                     //Getter for the Wait Time
	int GetN();                                                      //Getter for the number of IOs
	Process*& GetParent();                                            //Getter for the parent
	Process*& GetFirstChild();                                        //Getter for the first child
	Process*& GetSecondChild();                                       //Getter for the second child
	int GetRunningFor();                                             //Getter for how long the process has been running so far
	void GetFirstIO(IO*& ioTemp);                                    //Getter for the front IO in the IOs queue
	bool CheckIO_D();
	bool AddChild(Process* child);                                   //Add a forked child to the process                           
	void AddIO(IO* io);                               
	void DecrementCT();                                              //decrements the CT by one 
	void IncrementRunningFor();                                      //Increments RunningFor by one 
	int WTsofar(int timestep);                                                   //Calculates the WT so far
	friend ostream& operator<<(ostream& output,Process &p);          //<< Operator overloading
    friend bool operator ==(Process& p1,Process& p2);                //== Operator Overloading 
	friend bool operator==(int value,Process& p);                    //== Operator Overloading when the Process ID is sent instead of 2 Processes
	int GetActualCT();
	void SetIO_D();			
	int GetIO_D();													
	void SetFirstChild(Process*p);
	void SetSecondChild(Process*p);
	~Process();                                                      //Destructor
};

