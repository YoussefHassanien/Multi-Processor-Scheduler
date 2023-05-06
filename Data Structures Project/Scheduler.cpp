#pragma once
#include "Scheduler.h"
#include "FCFS.h"
#include "RR.h"
#include "SJF.h"
#include "SIGKILL.h"

//Constructor
Scheduler::Scheduler(): UI(this)
{
	TimeSlice = 0;
	Processor_Count = 0;
	TimeStep = 1;
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
	RTF=0;
	MaxW=0;
	STL = 0;
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
		FCFS_ProcessorsCnt = stoi(fcfs);

		string sjf;
		InFile >> sjf;
		SJF_ProcessorsCnt = stoi(sjf);

		string rr;
		InFile >> rr;
		RR_ProcessorsCnt = stoi(rr);

		string timeslice;
		InFile >> timeslice;
		TimeSlice = stoi(timeslice);
		string rtf;
		InFile >> rtf;
		RTF = stoi(rtf);
		string maxw;
		InFile >> maxw;
		MaxW = stoi(maxw);
		string stl;
		InFile >> stl;
		STL = stoi(stl);
		string Fork;
		InFile >> Fork;
		ForkProb = stoi(Fork);
		string processes;
		InFile >> processes;
		LastProcessID = stoi(processes);
		for (int i = 0; i < LastProcessID; i++)
		{
			//loop on the processes and read the data members of each
			Process* p = new Process;
			string AT, PID, CT, N;
			InFile >> AT >> PID >> CT >> N;
			p->SetAT(stoi(AT));
			p->SetID(stoi(PID));
			p->SetCT(stoi(CT));
			p->SetN(stoi(N));
			LinkedQueue<IO*>* IOq= new LinkedQueue<IO*>;
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
				p->AddIO(io);
				continue;

			}
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
		for (int i = 0; i < FCFS_ProcessorsCnt; i++)
		{
			Processor* p = new FCFS(this,Processor_Count + 1);
			PArr[Processor_Count] = p;
			Processor_Count++;
		}
		for (int i = 0; i < SJF_ProcessorsCnt; i++)
		{
			Processor* p = new SJF(this,Processor_Count + 1);
			PArr[Processor_Count] = p;
			Processor_Count++;
		}
		for (int i = 0; i < RR_ProcessorsCnt; i++)
		{
			Processor* p = new RoundRobin(this,Processor_Count + 1, TimeSlice);
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
	terminatedlist.enqueue(p);
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
//Getter for the forking probability
int Scheduler::getForkProb()
{
	return ForkProb;
}
//Getter for the timestep
int Scheduler::getTimeStep()
{
	return TimeStep;
}


//Checks if all the processes are terminated
bool Scheduler::AllIsTerminated()
{
	return TerminatedProcesses == LastProcessID;

}

//Simulation function
void Scheduler::simulation()
{

	int random;
	Process* TempProc;;
	IO* ioTemp;
	readfileparameters();
	while (!AllIsTerminated())
	{
        
		Process* p=nullptr;
		for (int i = 0; i < LastProcessID; i++) 
		{
			if (!newlist.isEmpty())
			{
				newlist.peek(p);
				AddtoRdyLists(p);
			}
		}
		

		for (int i = 0; i < Processor_Count; i++) 
		{

			
			//Process migration 
			
			//if (FCFS* FCFSptr = dynamic_cast<FCFS*>(PArr[i]))  // the current processor is a FCFS processor
			//{
			//	FCFSptr->FCFStoRR_Migration();
			//}
			//else if (RoundRobin* RRptr = dynamic_cast<RoundRobin*>(PArr[i])) // the current processor is a RR processor 
			//{
			//	RRptr->RRtoSJF_Migration();
			//}

			
			PArr[i]->ScheduleAlgo(); //rdy to run and run to rdy

			//Run to TRM
			if (PArr[i]->getRunning()) {
				Process* CurrentRunning = PArr[i]->getRunning(); //moves to terminated if ct =0
				if (CurrentRunning->GetCT() == 0)
				{
					addToTrm(CurrentRunning);
					PArr[i]->SetRunning(nullptr);
					PArr[i]->setisbusy(false);
					DecrementRunningCount();
					continue;
				}

				//Run to BLK
				if (CurrentRunning->GetN() != 0) //checks if the current process needs IO
				{
					CurrentRunning->GetFirstIO(ioTemp); 
					if (ioTemp!=nullptr) {
						if (ioTemp->GetRequest() == TimeStep) //checks if the IO_R equals the current timestep //add a data member that counts execution time
						{
							addtoblocklist(CurrentRunning);
							PArr[i]->SetRunning(nullptr);
							PArr[i]->setisbusy(false);
							DecrementRunningCount();
						}
					}
				}

				
			}

		}
		//BLK to RDY
		if (!blocklist.isEmpty()) //check BLK list
		{
			for (int i = 0; i < BLKCount; i++)
			{
				blocklist.dequeue(TempProc);
				if (TempProc->CheckIO_D())  //CheckIO_D needs further modifications
				{
					Set_ShortestListIdx();
					PArr[ShortestListIdx]->AddToRdy(TempProc);
					BLKCount--;
				}
				else
					blocklist.enqueue(TempProc);
			}

		}
		WorkStealing();
		UI.PrintInteractiveMode();
		TimeStep++;
	}


}


//Moves the process from NEW list to RDY list
void Scheduler::AddtoRdyLists(Process*p)
{
<<<<<<< HEAD
	if (p->GetAT() == TimeStep)
	{
		newlist.dequeue(p);
		for (int i = 0; i < Processor_Count; i++)
=======
	if (p) {
		if (p->GetAT() == TimeStep)
>>>>>>> f9fd989a6981ec1623eb17254de2d98bd59504ad
		{
			newlist.dequeue(p);

			for (int i = 0; i < Processor_Count; i++)
			{
				if (PArr[i]->SumCT() == 0)
				{
					PArr[i]->AddToRdy(p);
					return;
				}
			}
			Set_ShortestListIdx();
			PArr[ShortestListIdx]->AddToRdy(p);
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


//Setter for the Shortest FCFS List Index
void Scheduler::Set_ShortestFCFS()
{
	ShortestFCFSListIdx = 0;
	for (int i = 0; i < SJF_ProcessorsCnt; i++)
		if (PArr[i]->SumCT() < PArr[ShortestFCFSListIdx]->SumCT())
			ShortestFCFSListIdx = i;
}

//Getter for the Shortest FCFS List Index
int Scheduler::Get_ShortestFCFS()
{
	return ShortestFCFSListIdx;
}

//Setter for the Shortest SJF List Index
void Scheduler::Set_ShortestSJF()
{
	ShortestSJFListIdx = FCFS_ProcessorsCnt;
	for (int i = FCFS_ProcessorsCnt; i < RR_ProcessorsCnt; i++)
		if (PArr[i]->SumCT() < PArr[ShortestSJFListIdx]->SumCT())
			ShortestSJFListIdx = i;
}

//Getter for the Shortest SJF List Index
int Scheduler::Get_ShortestSJF()
{
	return ShortestSJFListIdx;
}

//Setter for the Shortest RR List Index
void Scheduler::Set_ShortestRR()
{
	ShortestRRListIdx = SJF_ProcessorsCnt;
	for (int i = SJF_ProcessorsCnt; i < RR_ProcessorsCnt; i++)
		if (PArr[i]->SumCT() < PArr[ShortestRRListIdx]->SumCT())
			ShortestRRListIdx = i;
}

//Getter for the Shortest RR List Index
int Scheduler::Get_ShortestRR()
{
	return ShortestRRListIdx;
}

//Takes the running process from the RR processor and inserts it in the shortest SJF RDY queue
void Scheduler::FromRRtoShortestSJF(Process* p)
{
	PArr[ShortestSJFListIdx]->AddToRdy(p);
}

//Takes the running process from the RR processor and inserts it in the shortest SJF RDY queue
void Scheduler::FromFCFStoShortestRR(Process* p)
{
	PArr[ShortestRRListIdx]->AddToRdy(p);
}

//Getter for RTF 
int Scheduler::GetRTF()
{
	return RTF;
}

//Getter for MaxW
int Scheduler::GetMaxW()
{
	return MaxW;
}
void Scheduler::IntiateForking(Process*running)
{
	if (running)
	{
		int RandomForkProb = generaterandom(1, 100);
		if (RandomForkProb > 0 && RandomForkProb <= ForkProb)
		{
			LastProcessID++;
			Process* child = new Process(TimeStep, LastProcessID, running->GetCT());
			child->SetParent(running);
			running->AddChild(child);
		}
	}
}

void Scheduler::Set_LongestListIdx()
{
	LongestListIdx = 0;
	for (int i = 1; i < Processor_Count; i++)
	{
		if (PArr[i]->GetTotalCT() < PArr[LongestListIdx]->GetTotalCT())
			LongestListIdx = i;
	}
}

void Scheduler::WorkStealing()
{
		float Steal_Limit;
		Process* p = NULL;
		Set_ShortestListIdx(); //loops on the processors array to set the shortest index to the shortest list
		Set_LongestListIdx(); //loops on the processors array to set the longest index to the longest list
		Steal_Limit = (float)(PArr[LongestListIdx]->SumCT() - PArr[ShortestListIdx]->SumCT()) / PArr[LongestListIdx]->SumCT();
		if (Steal_Limit < 0.4)
			return;
		if (TimeStep == 0 || TimeStep % STL != 0)
			return;
		PArr[LongestListIdx]->deleteprocess(p);
		PArr[ShortestListIdx]->AddToRdy(p);
		WorkStealing(); // calls the function recursively until one of the exit conditions is satisfied 

	
}


