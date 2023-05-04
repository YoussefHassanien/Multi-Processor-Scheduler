#ifndef SCHEDULER_H
#define SCHEDULER_H
#pragma once
using namespace std;
class Processor;
class UI_Info;
#include<iostream>
#include <fstream>
#include<string>
#include "Process.h"
#include "LinkedList.h"
#include "Processor.h"
#include "LinkedQueue.h"
#include "SIGKILL.h"
#include "UI_Info.h"
#include<random>
class Scheduler
{
private:

	string FLName;                         //File name
	Processor* PArr[500];                  //Array of processors pointers 
	LinkedQueue<Process*> newlist;         //NEW list
	LinkedQueue<Process*>blocklist;        //BLK list
	LinkedQueue<Process*>terminatedlist;   //TRM list
	LinkedList<Process*>FamilyList;        // a list of pointers to the parent and its children and grandchildren
	int Processor_Count;                   //Total count of processors
	int FCFS_ProcessorsCnt;                //Count of the FCFS processors
	int RR_ProcessorsCnt;                  //Count of the RR processors 
	int SJF_ProcessorsCnt;                 //Count of the SJF processors
	SIGKILL* SigKillarr[500];              //Array of signal kill pointers 
	int TimeStep;                          //Time step
	int TimeSlice;                         //Time slice
	int LastProcessID;                     //processes count for all processes in the program
	int RTF;                               //RTF read from the input file
	int MaxW;                              //MaxW read from the input file
	int ForkProb;                          //Forking probability read from the input file
	int STL;                               //The Time at which the stealing action occurs  
	int TerminatedProcesses;               //counter for all terminated processes
	UI_Info UI;                            //Pointer to the UI info class
	int BLKCount;                          //Number of processes in the BLK list
	int RunningCount;                      //Number of processes currently in the running state
	int counter;                           //Counter to add to RdyLists of processors 
	int AvgWT;                             //Average Waiting time of all Processes
	int AvgRT;                             //Average Response time of all Processes
	int AvgTRT;                            //Average Turnaround Time of all Processes
	int AvgRTF;                            //Average RTF time of all Processes
	int MigPercent;                        //Percentage of Process Migration due to RTF and MaxW
	int StealPercent;                      //Percentage of Process moved by Work Steal
	int KillPercent;                       //Percentage of Process Kill
	int ForkPercent;                       //Percentage of Process Fork
	int AvgUtil;                           //Average Utilization for all Processors
	int StealLimitPercent;                 //This percentage should be less than 40% and if it exeeds this percentage the stealing between processor should start
	int ShortestListIdx;                   //Index of the processor with the shortest ready list
	int ShortestFCFSListIdx;               //Index of the FCFS processor with the shortest ready list
	int ShortestSJFListIdx;                //Index of the SJF processor with the shortest ready list
	int ShortestRRListIdx;                 //Index of the RR processor with the shortest ready list


public:
	Scheduler();                          //Constructor 
	~Scheduler();                         //Destructor
	void setfilename(string& s);          //Setter for the file name
	void readfileparameters();            //Function to read the input file
	void addtonewlist(Process* p);        //Adds a process to the NEW list 
	void addtoblocklist(Process*& p);     //Adds a process to the BLK list
	void addToTrm(Process*& p);           //Adds a process to the terminated list
	int getprocessorcount();              //Getter for the total number of processors 
	void incrementprocessorcount();       //increments the count of processors once a new processor is declared
	int generaterandom(int min, int max); //Generates a random number between a max and a min value
	int getForkProb();                    //Getter for the forking probability
	int getTimeStep();                    //Getter for the timestep
	bool AllIsTerminated();               //checks that all ready lists are empty and all processors are idle
	void simulation();                    //Simulation function
	void AddtoRdyLists(int& counter);     //Moves the process from NEW list to RDY list
	void PrintProcessorList();            //Prints the processor list
	int getBLKCount();                    //Getter for the count of blocked processes
	void incrementRunningCount();         //Increments the number of running processes by one 
	void DecrementRunningCount();         //Decrements the number of running processes by one 
	void PrintBLKList();                  //Prints the BLK list
	void PrintTRMList();                  //Prints the TRM list
	void PrintRunningList();              //Prints the running processes
	void Set_ShortestListIdx();           //Setter for the Shortest List Index
<<<<<<< HEAD
	int Get_ShortestLlistIdx();			  //Getter for the Shortest List Index
	void Set_ShortestFCFS();			  //Setter for the Shortest FCFS List Index
=======
	int Get_ShortestLlistIdx();           //Getter for the Shortest List Index
	void Set_ShortestFCFS();              //Setter for the Shortest FCFS List Index 
>>>>>>> 8030d642fdce49c7abd57bd377a005f2885c6ff6
	int Get_ShortestFCFS();               //Getter for the Shortest FCFS List Index
	void Set_ShortestSJF();               //Setter for the Shortest SJF List Index
	int Get_ShortestSJF();                //Getter for the Shortest SJF List Index
	void Set_ShortestRR();                //Setter for the Shortest RR List Index
	int Get_ShortestRR();                 //Getter for the Shortest RR List Index
	void FromRRtoShortestSJF(Process*p);  //Takes the running process from the RR processor and inserts it in the shortest SJF RDY queue
	void FromFCFStoShortestRR(Process* p);//Takes the running process from the FCFS processor and inserts it in the shortest RR RDY queue
	int GetRTF();                         //Getter for the RTF
	int GetMaxW();                        //Getter for the MaxW
	void IntiateForking(Process* running);//The Function that checks if the running process in the FCFS will fork or not then makes all the necessary operations if it will
	//void AddtoFCFS_RDY(int Processor_id); //Adds the forked process to the right FCFS ready queue
};
#endif