#pragma once
#include "Scheduler.h"
#include "FCFS.h"
#include "RR.h"
#include "SJF.h"
#include "SIGKILL.h"
#include <iomanip>

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
	StealedProcesses = 0;
	KillPercent = 0;
	ForkPercent = 0;
	AvgUtil = 0;
	StealLimitPercent = 0;
	RTF=0;
	MaxW=0;
	STL = 0;
	Output = "OutputFile";
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
			//LinkedQueue<IO*>* IOq= new LinkedQueue<IO*>;
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
				

			}
			addtonewlist(p);
		}
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
			FCFS* TempFCFS = new FCFS(this);
			TempFCFS->AddKillingSignal(SigKillPtr);
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


void Scheduler::PrintOutputFile() //still in progress
{
	Output += ".txt";
	ofstream OutFile;
	OutFile.open(Output, ios::out);
	const char separator = ' ';
	const int nameWidth = 6;
	const int numWidth = 8;
	OutFile<< left << setw(nameWidth) << setfill(separator) << "TT";
	OutFile << left << setw(nameWidth) << setfill(separator) << "PID";
	OutFile << left << setw(nameWidth) << setfill(separator) << "AT";
	OutFile << left << setw(nameWidth) << setfill(separator) << "CT";
	OutFile << left << setw(nameWidth) << setfill(separator) << "IO_D"<<"      ";
	OutFile << left << setw(nameWidth) << setfill(separator) << "WT";
	OutFile << left << setw(nameWidth) << setfill(separator) << "RT";
	OutFile << left << setw(nameWidth) << setfill(separator) << "TRT";
	OutFile << endl;
	int TotalWT=0;
	int TotalTRT=0;
	int TotalRT=0;
	for (int i = 0; i < LastProcessID; i++)
	{
		Process* p = nullptr;
		terminatedlist.dequeue(p);
		OutFile << left << setw(nameWidth) << setfill(separator) << p->GetTT();
		OutFile << left << setw(nameWidth) << setfill(separator) << p->GetID();
		OutFile << left << setw(nameWidth) << setfill(separator) << p->GetAT();
		OutFile << left << setw(nameWidth) << setfill(separator) << p->GetActualCT();
		OutFile << left << setw(nameWidth) << setfill(separator) << p->GetIO_D() << "      ";
		OutFile << left << setw(nameWidth) << setfill(separator) << p->GetWT();
		OutFile << left << setw(nameWidth) << setfill(separator) << p->GetRT();
		OutFile << left << setw(nameWidth) << setfill(separator) << p->GetTRT();
		OutFile << endl;
		TotalWT += p->GetWT();
		TotalTRT += p->GetTRT();
		TotalRT += p->GetRT();
	}
	OutFile << "Processes: " << LastProcessID << endl;
	OutFile << "Avg WT = " << TotalWT / LastProcessID << ",       Avg RT = " << TotalRT / LastProcessID << ",       Avg TRT = " << TotalTRT / LastProcessID << endl;
	OutFile << "Migration %:" << "       RTF=" << "%,       MaxW=" << "%" << endl;   //TBC
	OutFile << "Work Steal%: " <<((float) StealedProcesses/LastProcessID)*100<< "%" << endl;
	OutFile << "Forked Processes :" << "%" << endl;   //TBC
	OutFile << "Killed Processes :" << "%" << endl;   //TBC
	OutFile << endl << endl;
	OutFile << "Processor: " << Processor_Count << " ["<<FCFS_ProcessorsCnt<<" FCFS, "<<SJF_ProcessorsCnt<<" SJF, "<<RR_ProcessorsCnt<<" RR]" << endl;
	OutFile << "Processors Load" << endl;
	for (int i = 0; i < Processor_Count; i++)
	{
		OutFile << "p" << PArr[i]->getID() << "=" << PArr[i]->GetPLoad() * 100 << "%,    ";
	}
	OutFile << endl<<endl;
	OutFile << "Processors Utiliz" << endl;
	int TotalUtiliz = 0;
	for (int i = 0; i < Processor_Count; i++)
	{
		OutFile << "p" << PArr[i]->getID() << "=" << PArr[i]->GetPUtil() * 100 << "%,    ";
		TotalUtiliz += PArr[i]->GetPUtil() * 100;
	}
	OutFile << endl << "Avg utilization = " << ((float)TotalUtiliz / Processor_Count)*100<<"%";

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
void Scheduler::addToTrm(Process* p)
{
	if (p)
	{
		terminatedlist.enqueue(p);
		TerminatedProcesses++;
		p->SetTT(TimeStep); //sets the termination time of the process with the current timestep;
		IncrementTotalTRT(p->GetTRT());  //increments the total TRT
	}
	
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
		
		Process* p = nullptr;
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
			PArr[i]->ScheduleAlgo(); //rdy to run and run to rdy

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
			/*if (!terminatedlist.isEmpty())
			{
				Process* p = nullptr;
				terminatedlist.dequeue(p);
				cout <<p->GetID()<<" " << p->GetWT() << " " << p->GetTRT() << " " << p->GetRT() << endl;
			}
			else
				cout << "terminated empty..."<<endl;*/
	WorkStealing();
	UI.printInterface();
	TimeStep++;
		


	}
	PrintOutputFile();
}


//Moves the process from NEW list to RDY list
void Scheduler::AddtoRdyLists(Process*p)
{
	if (p) {
		if (p->GetAT() == TimeStep)
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
		LastProcessID++;
		Process* child = new Process(TimeStep, LastProcessID, running->GetCT());
		child->SetParent(running);
		running->AddChild(child);
		Set_ShortestFCFS();
		PArr[ShortestFCFSListIdx]->AddToRdy(child);
		ParentsList.InsertEnd(running);
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
//work stealing

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
		PArr[LongestListIdx]->DeleteProcess(p);
		PArr[ShortestListIdx]->AddToRdy(p);
		StealedProcesses++;
		WorkStealing(); // calls the function recursively until one of the exit conditions is satisfied 

	
}

void Scheduler::AddChildrenToTrm(Process* parent)
{
	if ((!parent->GetFirstChild()) && (!parent->GetSecondChild())) 
		return;
	else
	{
		if (parent->GetFirstChild())
		{
			Process* Child1 = new Process(parent->GetFirstChild()->GetAT(), parent->GetFirstChild()->GetID(), parent->GetFirstChild()->GetCT());
			addToTrm(Child1);
			AddChildrenToTrm(parent->GetFirstChild());
		}
		if (parent->GetSecondChild())
		{
			Process* Child2 = new Process(parent->GetSecondChild()->GetAT(), parent->GetSecondChild()->GetID(), parent->GetSecondChild()->GetCT());
			addToTrm(Child2);
			AddChildrenToTrm(parent->GetSecondChild());
		}
	}

}

bool Scheduler::ParentKilling(Process* parent)
{
	if (!ParentsList.isEmpty()) //Checks if the parents list is empty or not
	{
		if (ParentsList.Find(parent)) //Checks if the current running process is in the parents list or not
		{
			AddChildrenToTrm(parent); //Since the current running process is in the parents list and it is being terminated so its children must be terminated too
			
			if (parent->GetFirstChild()) //Checks if the parent has first child
			{
				for (int i = 0; i < FCFS_ProcessorsCnt; i++)
				{
					if (PArr[i]->Search(parent->GetFirstChild()))
					{
						PArr[i]->DeleteProcess(parent->GetFirstChild()); 
					}
				}
			} 
			else 
				if (parent->GetSecondChild()) //Checks if the parent has second child
				{
					for (int i = 0; i < FCFS_ProcessorsCnt; i++)
					{
						if (PArr[i]->Search(parent->GetSecondChild()))
						{
							PArr[i]->DeleteProcess(parent->GetSecondChild());  //i think this might cause a null access violation as the the delete takes the value by refrence and makes it point to null after removing it from the nodes
						}
					}
				}
			return true;
		}
		return false;
	}
	return false;
}

void Scheduler::IncrementTotalTRT(int trt)
{
	TotalTRT += trt;
}

int Scheduler::GetTotalTRT()
{
	return TotalTRT;
}


