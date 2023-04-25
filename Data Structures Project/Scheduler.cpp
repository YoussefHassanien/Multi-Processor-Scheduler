#pragma once
#include "Scheduler.h"
#include "FCFS.h"
#include "RR.h"
#include "SJF.h"
#include "SIGKILL.h"

//Constructor
Scheduler::Scheduler(): UI(this)
{
	timeSlice = 0;
	Processor_Count = 0;
	timestep = 1;
	ForkProb = 0;
	TerminatedProcesses = 0;
	BLKCount = 0;
	RunningCount = 0;
	counter = 0;
	AvgWT = 0;
	AvgRT = 0;
	AvgTRT = 0;
	AvgRTF = 0;
	MigPercent = 0;
	StealPercent = 0;
	KillPercent = 0;
	ForkPercent = 0;
	AvgUtil = 0;
	StealLimitPercent = 0;
}

//destructor
Scheduler::~Scheduler()
{
}

//Setter for the file name
void Scheduler::setfilename(string& s)
{
	FLName = s;
}

//Function to read the input file
void Scheduler::readfileparameters()
{
	FLName;
	FLName += ".txt";
	ifstream InFile;
	InFile.open(FLName, ios::in);
	if (InFile.is_open())
	{
		//read from the file the number of the processors and processes  
		Process* p = NULL;
		string fcfs;
		InFile >> fcfs;
		int intfcfs = stoi(fcfs);


		string sjf;
		InFile >> sjf;
		int intsjf = stoi(sjf);


		string rr;
		InFile >> rr;
		int intrr = stoi(rr);


		string timeslice;
		InFile >> timeslice;
		int inttimeslice = stoi(timeslice);
		string RTF;
		InFile >> RTF;
		int intRTF = stoi(RTF);
		string MaxW;
		InFile >> MaxW;
		int intMaxW = stoi(MaxW);
		string STL;
		InFile >> STL;
		int intSTL = stoi(STL);
		string Fork;
		InFile >> Fork;
		int forkprob = stoi(Fork);
		string processes;
		InFile >> processes;
		int processesno = stoi(processes);
		LastProcessID = processesno;
		Set_Last_Child_ID(LastProcessID);
		for (int i = 0; i < processesno; i++)
		{
			//loop on the processes and read the data members of each
			Process* p = new Process;
			string AT, PID, CT, N;
			InFile >> AT >> PID >> CT >> N;
			p->SetAT(stoi(AT));
			p->SetID(stoi(PID));
			p->SetCT(stoi(CT));
			p->SetN(stoi(N));
			IO** IOarr = new IO*[stoi(N)];
			for (int i = 0; i < stoi(N); i++)
			{
				string openbracket;
				InFile >> openbracket;
				string IO_R;
				InFile >> IO_R;
				int intIO_R = stoi(IO_R);
				string comma;
				InFile >> comma;
				string IO_D;
				InFile >> IO_D;
				int intIO_D = stoi(IO_D);
				string closingbracket;
				InFile >> closingbracket;
				InFile >> comma;
				IO* io= new IO;
				io->SetDuration(intIO_D);
				io->SetRequest(intIO_R);
				IOarr[i] = io;
				continue;

			}
			p->AddIO(IOarr);
			addtonewlist(p);
		}
		int i = 0;
		string sigkill;
		InFile >> sigkill;
		InFile >> sigkill;
		while (!InFile.eof())
		{
			string killTime;
			InFile >> killTime;
			int intkillTime = stoi(killTime);
			string ProcessID;
			InFile >> ProcessID;
			int intProcessID = stoi(ProcessID);
			SIGKILL* SigKillPtr = new SIGKILL(intProcessID, intkillTime);
			SigKillarr[i] = SigKillPtr;
			i++;
			continue;
		}
		for (int i = 0; i < intfcfs; i++)
		{
			Processor* p = new FCFS(this,Processor_Count + 1, forkprob);
			PArr[Processor_Count] = p;
			Processor_Count++;
		}
		for (int i = 0; i < intsjf; i++)
		{
			Processor* p = new SJF(this,Processor_Count + 1);
			PArr[Processor_Count] = p;
			Processor_Count++;
		}
		for (int i = 0; i < intrr; i++)
		{
			Processor* p = new RoundRobin(this,Processor_Count + 1, inttimeslice);
			PArr[Processor_Count] = p;
			Processor_Count++;
		}
	}
	else {
		cout << "file not oppened" << endl; //failed to load the file 
	}
}

//Adds a process to the NEW list 
void Scheduler::addtonewlist(Process* p)
{
	newlist.enqueue(p);
}

//Adds a process to the BLK list 
void Scheduler::addtoblocklist(Process*& p)
{
	blocklist.enqueue(p);
	BLKCount++;
}

//Adds a process to the TRM list 
void Scheduler::addToTrm(Process*& p)
{
	terminatedlist.dequeue(p);
	TerminatedProcesses++;
}

//Getter for the total number of processors 
int Scheduler::getprocessorcount()
{
	return Processor_Count;
}

//increments the count of processors once a new processor is declared
void Scheduler::incrementprocessorcount()
{
	Processor_Count++;
}

//Generates a random number between a max and a min value
int Scheduler::generaterandom(int min, int max)
{
	//Seed the random number generator
	std::random_device Random; 
	std::mt19937 gen(Random());
	
	//Define the distribution for the random number
	std::uniform_int_distribution<> dis(min, max);
	
	//Generate and return the Rabdom Number
	return dis(gen);
}

//Getter fo rth eforking probability
int Scheduler::getForkProb()
{
	return ForkProb;
}

//Getter for the child ID
int Scheduler::getChildID()
{
	return ChildID;
}

//Increments the child ID by one
void Scheduler::incrementChildID()
{
	ChildID++;
}

//Getter for the timestep
int Scheduler::getTimeStep()
{
	return timestep;
}


//Checks if all the processes are terminated
bool Scheduler::AllIsTerminated()
{
	return TerminatedProcesses == (ChildID - 1);

}

//Simulation function
void Scheduler::simulation()
{

	int random;
	Process* TopBlock=NULL;
	readfileparameters();
	while (!AllIsTerminated())
	{

		for (int i = 0; i < LastProcessID; i++)
		{
			AddtoRdyLists(counter);
		}

		for (int i = 0; i < Processor_Count; i++)
		{
			PArr[i]->ScheduleAlgo();
		}
		//random = generaterandom(1, 100);
		//if (random < 10 && !blocklist.isEmpty()) 
		//{
		//	blocklist.dequeue(TopBlock);
		//	if (TopBlock!=NULL)
		//	{
		//		int randProcessor = generaterandom(0, Processor_Count - 1);
		//		PArr[randProcessor]->AddToRdy(TopBlock);
		//		BLKCount--;
		//	}
		//}

		//int TermRand = generaterandom(1, (ChildID-1));
		//for (int i = 0; i < Processor_Count; i++)
		//{
		//	PArr[i]->RandomTermination(TermRand);
		//}

		UI.PrintInteractiveMode();
		timestep++;
	}


}



//Moves the process from NEW list to RDY list
void Scheduler::AddtoRdyLists(int& counter)
{
	Process* Temp;
	if (!newlist.isEmpty())
	{
		newlist.peek(Temp);
		if (Temp->GetAT() == timestep)
		{
			newlist.dequeue(Temp);
			int i1 = counter % Processor_Count;
			PArr[i1]->AddToRdy(Temp);
			counter++;
		}
	}


}

//Prints the processor list
void Scheduler::PrintProcessorList()
{
	for (int i = 0; i < Processor_Count; i++)
	{
		cout << *PArr[i] << endl;
	}
}

//Getter for the count of blocked processes
int Scheduler::getBLKCount()
{
	return BLKCount;
}

//Increments the number of running processes by one 
void Scheduler::incrementRunningCount()
{
	RunningCount++;
}

//Decrements the number of running processes by one 
void Scheduler::DecrementRunningCount()
{
	RunningCount--;
}

//Prints the BLK list
void Scheduler::PrintBLKList()
{
	cout << BLKCount << " BLK: ";
	blocklist.Print();
}

//Prints the TRM list
void Scheduler::PrintTRMList()
{
	cout << TerminatedProcesses << " TRM: ";
	terminatedlist.Print();
}

//Prints the running processes  
void Scheduler::PrintRunningList()
{
	cout << RunningCount << " RUN: ";
	for (int i = 0; i < Processor_Count; i++)
	{
		if (PArr[i]->getRunning())
			cout << *PArr[i]->getRunning() << "(P" << i + 1 << "), ";
	}
}

//Setter for the last child ID
void Scheduler::Set_Last_Child_ID(int x)
{
	ChildID = x + 1;
}

void Scheduler::Set_ShortestListIdx()
{
	ShortestListIdx = 0;
	for (int i = 1; i < Processor_Count; i++)
	{
		if (PArr[i]->GetTotalCT() < PArr[ShortestListIdx]->GetTotalCT())
			ShortestListIdx = i;
	}
}

int Scheduler::Get_ShortestLlistIdx()
{
	return ShortestListIdx;
}
