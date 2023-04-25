#pragma once
#include<iostream>
#include"IO.h"
#include "Scheduler.h"
#include"BinaryTree.h"
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
		;
	Scheduler* s;
	IO** IOArr = new IO*[N]; //Array of pointers to the IOs of the Process
	BinaryTree<Process>* ChildsTree; //A Tree of the forked childs
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
	void SetN(int n);
	int GetID();                                                     //Getter for the process ID 
	int GetAT();                                                     //Getter for the Arrival Time
	int GetRT();                                                     //Getter for the Arrival Time
	int GetCT();                                                     //Getter for the CPU time
	int GetTT();                                                     //Getter for the Termination time
	int GetTRT();                                                    //Getter for the Turnarround time
	int GetWT();                                                     //Getter for the Wait Time
	int GetN();
	void AddChild(int t, int rct);                                   //Create a new child
	void AddIO(IO* Arr[]);                                           //Adds IO
	bool GetOrph();                                                  //Getter for the orphan
	Process* GetChildPtr();                                          //Returns a pointer to the child
	void SetOrph(bool orph);                                         //Setter for the orphan
	void SetS(int s);
	void SetChildPtr(Process* Ptr);                                  //Setter for the child pointer
	void PrintProcessInfo();                                         //Prints the Processes info
	void DecrementCT();                                              //decrements the CT by one 
	 friend ostream& operator<<(ostream& output,Process &p);         //Operator overloading
	~Process();                                                      //Destructor
};

