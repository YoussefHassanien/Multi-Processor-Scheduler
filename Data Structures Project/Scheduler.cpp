#pragma once
#include "Scheduler.h"
#include "FCFS.h"
#include "RR.h"
#include "SJF.h"
#include "SIGKILL.h"
#include "EDF.h"
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
	KilledCount = 0;
	ForkPercent = 0;
	AvgUtil = 0;
	StealLimitPercent = 0;
	RTF=0;
	MaxW=0;
	StopTime = 0;
	STL = 0;
	Output = "OutputFile";
	OriginalProcessesCount = 0;
}

//destructor
Scheduler::~Scheduler()
{
	Process* p = nullptr;
	for (int i = 0; i < Processor_Count; i++)
	{
		delete PArr[i];
		PArr[i] = nullptr;
	}
	for (int i = 0; i < TerminatedProcesses; i++)
	{
		
		terminatedlist.dequeue(p);
		delete p;
	}
	p = nullptr;
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

		string edf;
		InFile >> edf;
		EDF_ProcessorCnt = stoi(edf);

		string timeslice;
		InFile >> timeslice;
		TimeSlice = stoi(timeslice);
		string stoptime;
		InFile >> stoptime;
		StopTime = stoi(stoptime);
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
		OriginalProcessesCount = LastProcessID;
		for (int i = 0; i < LastProcessID; i++)
		{
			//loop on the processes and read the data members of each
			Process* p = new Process;
			string AT, PID, CT, Deadline, N;
			InFile >> AT >> PID >> CT >> Deadline >> N;
			p->SetAT(stoi(AT));
			p->SetID(stoi(PID));
			p->SetCT(stoi(CT));
			p->SetDeadline(stoi(Deadline));
			p->SetN(stoi(N));
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
			SIGKILL* SigKillPtr = new SIGKILL(intkillTime, intProcessID);
			FCFS* TempFCFS = new FCFS(this, ForkProb);
			TempFCFS->AddKillingSignal(SigKillPtr);
			delete TempFCFS;
			TempFCFS = nullptr;
		}
		for (int i = 0; i < FCFS_ProcessorsCnt; i++)
		{
			Processor* p = new FCFS(this, ForkProb,Processor_Count + 1);
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
			Processor* p = new RoundRobin(this,Processor_Count + 1, TimeSlice,RTF);
			PArr[Processor_Count] = p;
			Processor_Count++;
		}
		for (int i = 0; i < EDF_ProcessorCnt; i++)
		{
			Processor* p = new EDF(this, Processor_Count + 1);
			PArr[Processor_Count] = p;
			Processor_Count++;
		}
	}
	else {
		cout << "file not oppened" << endl; //failed to load the file 
		exit(0);
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
	OutFile << "Migration %:" << "       RTF=" <<(int)(((float)TotalMigFromRRToSJF/LastProcessID)*100) << "%,       MaxW=" << (int)(((float)TotalMigFromFCFSToRR / LastProcessID) * 100) << "%" << endl;   
	OutFile << "Work Steal%: " <<(int)(((float) StealedProcesses)/LastProcessID*100)<< "%" << endl;
	OutFile << "Forked Processes :" <<(int)(((float)(LastProcessID-OriginalProcessesCount)/LastProcessID)*100) <<"%" << endl;
	OutFile << "Killed Processes :" << (int)(((float)(KilledCount) / LastProcessID) * 100) << "% " << endl;   
	OutFile << "Processes finished before their deadline :" << (int)(((float)(FinishedBeforeDL) / LastProcessID) * 100) << "% " << endl;
	OutFile << endl << endl;
	OutFile << "Processor: " << Processor_Count << " ["<<FCFS_ProcessorsCnt<<" FCFS, "<<SJF_ProcessorsCnt<<" SJF, "<<RR_ProcessorsCnt<<" RR, " << EDF_ProcessorCnt << " EDF]" << endl;
	OutFile << "Processors Load" << endl;
	for (int i = 0; i < Processor_Count; i++)
	{
		OutFile << "p" << PArr[i]->getID() << "=" << (int)(PArr[i]->GetPLoad(TotalTRT) * 100) << "%,    ";
	}
	OutFile << endl<<endl;
	OutFile << "Processors Utiliz" << endl;
	float TotalUtiliz = 0;
	for (int i = 0; i < Processor_Count; i++)
	{
		float PUtil;
		PArr[i]->GetPUtil(PUtil);
		OutFile << "p" << PArr[i]->getID() << "=" << (int)(PUtil * 100) << "%,    ";
		TotalUtiliz += PUtil;
	}
	float AvgUtil = round(((TotalUtiliz / Processor_Count) * 100) * 100.0) / 100.0;          //to round it to 2 decimal places only 
	OutFile << endl << "Avg utilization = " << AvgUtil <<"%";

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
		if (TimeStep < p->GetDeadline())
			FinishedBeforeDL++;
		IncrementTotalTRT(p->GetTRT());  //increments the total TRT
	}
	
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


//Checks if all the processes are terminated
bool Scheduler::AllIsTerminated()
{
	return TerminatedProcesses == LastProcessID;

}

//Simulation function
void Scheduler::Simulation()
{
	Process* TempProcess;
	readfileparameters();
	while (TerminatedProcesses<LastProcessID)
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
			int random= generaterandom(1, 100);
			if (random == 1)
				PArr[i]->setOverHeating(true);
			PArr[i]->ScheduleAlgo(TimeStep,StopTime,RR_ProcessorsCnt,SJF_ProcessorsCnt); //rdy to run and run to rdy

		}
		if (FCFS_ProcessorsCnt)
		{
			FCFS TempFCFS(this, ForkProb, 0);
			SIGKILL* TempKillSig = nullptr;
			do
			{
				TempFCFS.KillingSigTime(TempKillSig, TimeStep);
				if (TempKillSig)
				{
					for (int i = 0; i < FCFS_ProcessorsCnt; i++)
					{
						if (PArr[i]->KillingSigAction(TempKillSig))
							break;
					}
				}
			} while (TempKillSig);
		}
		//BLK to RDY
		if (!blocklist.isEmpty()) //check BLK list
		{
				blocklist.peek(TempProcess);
				if (TempProcess->CheckIO_D())  
				{
					blocklist.dequeue(TempProcess);
					Set_ShortestListIdx();
					PArr[ShortestListIdx]->AddToRdy(TempProcess);
					BLKCount--;
				}
		}
	WorkStealing();
	UI.printInterface(TimeStep,BLKCount,TerminatedProcesses);
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
	
	blocklist.Print();
}


//Prints the TRM list
void Scheduler::PrintTRMList()
{
	
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
	for (int i = 0; i < Processor_Count; i++)
	{
		if (PArr[i]->GetTotalCT() == 0 && !PArr[i]->getOverHeating())
		{
			ShortestListIdx = i;
			return;
		}
	}
	for (int i = 0; i < Processor_Count; i++)
	{
		if (!PArr[i]->getOverHeating())
		{
			ShortestListIdx = i;
			break;
		}
	}
	for (int i = 0; i < Processor_Count; i++)
	{
		if (!PArr[i]->getOverHeating() && PArr[i]->GetTotalCT() < PArr[ShortestListIdx]->GetTotalCT())
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
	for (int i = 0; i < FCFS_ProcessorsCnt; i++)
	{
		if (PArr[i]->GetTotalCT() == 0 && !PArr[i]->getOverHeating())
		{
			ShortestFCFSListIdx = i;
			return;
		}
	}

	for (int i = 0; i < FCFS_ProcessorsCnt; i++)
	{
		if (!PArr[i]->getOverHeating())
		{
			ShortestFCFSListIdx = i;
			break;
		}
	}
	for (int i = 0; i < FCFS_ProcessorsCnt; i++)
	{
		if (!PArr[i]->getOverHeating() && PArr[i]->GetTotalCT() < PArr[ShortestFCFSListIdx]->GetTotalCT())
			ShortestFCFSListIdx = i;
	}
}

//Getter for the Shortest FCFS List Index
int Scheduler::Get_ShortestFCFS()
{
	return ShortestFCFSListIdx;
}

//Setter for the Shortest SJF List Index
void Scheduler::Set_ShortestSJF()
{
	for (int i = FCFS_ProcessorsCnt; i < (FCFS_ProcessorsCnt + SJF_ProcessorsCnt); i++)
	{
		if (PArr[i]->GetTotalCT() == 0 && !PArr[i]->getOverHeating())
		{
			ShortestSJFListIdx = i;
			return;
		}
	}
	for (int i = FCFS_ProcessorsCnt; i < (FCFS_ProcessorsCnt + SJF_ProcessorsCnt); i++)
	{
		if (!PArr[i]->getOverHeating())
		{
			ShortestSJFListIdx = i;
			break;
		}
	}
	for (int i = FCFS_ProcessorsCnt; i < (FCFS_ProcessorsCnt+SJF_ProcessorsCnt); i++)
		if (!PArr[i]->getOverHeating() && PArr[i]->GetTotalCT() < PArr[ShortestSJFListIdx]->GetTotalCT() )
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
	for (int i = SJF_ProcessorsCnt; i < (FCFS_ProcessorsCnt+SJF_ProcessorsCnt + RR_ProcessorsCnt); i++)
	{
		if (PArr[i]->GetTotalCT() == 0 && !PArr[i]->getOverHeating())
		{
			ShortestRRListIdx = i;
			return;
		}
	}
	for (int i = SJF_ProcessorsCnt; i < (FCFS_ProcessorsCnt + SJF_ProcessorsCnt + RR_ProcessorsCnt); i++)
	{
		if (!PArr[i]->getOverHeating())
		{
			ShortestRRListIdx = i;
			break;
		}
	}
	for (int i = SJF_ProcessorsCnt; i < (FCFS_ProcessorsCnt + SJF_ProcessorsCnt + RR_ProcessorsCnt); i++)
		if (!PArr[i]->getOverHeating() && PArr[i]->GetTotalCT() < PArr[ShortestRRListIdx]->GetTotalCT())
			ShortestRRListIdx = i;
}

//Getter for the Shortest RR List Index
int Scheduler::Get_ShortestRR()
{
	return ShortestRRListIdx;
}

//Takes the running process from the RR processor and inserts it in the shortest SJF RDY queue
bool Scheduler::FromRRtoShortestSJF(Process* p)
{
	Set_ShortestSJF();
	if (!PArr[ShortestSJFListIdx]->getOverHeating())
	{
		PArr[ShortestSJFListIdx]->AddToRdy(p);
		return true;
	}
	return false;
}

//Takes the running process from the RR processor and inserts it in the shortest SJF RDY queue
bool Scheduler::FromFCFStoShortestRR(Process* p)
{
	Set_ShortestRR();
	if (!PArr[ShortestRRListIdx]->getOverHeating())
	{
		PArr[ShortestRRListIdx]->AddToRdy(p);
		return true;
	}
	return false;
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
void Scheduler::IntiateForking(Process*Parent)

{
	if (Parent && (!Parent->GetFirstChild() || !Parent->GetSecondChild()))
	{
		Process* Child = nullptr;
		if (Parent->AddChild(Child));
		{
			LastProcessID++;
			Child = new Process(TimeStep, LastProcessID, Parent->GetCT());
			Parent->AddChild(Child);
			Child->SetParent(Parent);
			Set_ShortestFCFS();
			PArr[ShortestFCFSListIdx]->AddToRdy(Child);
		}
	}
}

void Scheduler::Set_LongestListIdx()
{
	LongestListIdx = 0;
	for (int i = 1; i < Processor_Count; i++)
	{
		if (!PArr[i]->getOverHeating() && PArr[i]->GetTotalCT() > PArr[LongestListIdx]->GetTotalCT() )
			LongestListIdx = i;
	}
}
//work stealing

void Scheduler::WorkStealing()
{
	if (TimeStep % STL != 0)
		return;
	else
	{
		float Steal_Limit;
		Process* p = NULL;
		do
		{
			Set_ShortestListIdx(); //loops on the processors array to set the shortest index to the shortest list
			Set_LongestListIdx(); //loops on the processors array to set the longest index to the longest list
			Steal_Limit = (float)(PArr[LongestListIdx]->GetTotalCT() - PArr[ShortestListIdx]->GetTotalCT()) / PArr[LongestListIdx]->GetTotalCT();
			if(Steal_Limit <= 0.4)
				break;
			else
			{
				PArr[LongestListIdx]->ReturnFirst(p);
				if (!p || p->GetParent())
					break;
				else
				{
					PArr[LongestListIdx]->DeleteProcess(p);
					PArr[ShortestListIdx]->AddToRdy(p);
					StealedProcesses++;
					if (LongestListIdx == ShortestListIdx)
						break;
					Steal_Limit = (float)(PArr[LongestListIdx]->GetTotalCT() - PArr[ShortestListIdx]->GetTotalCT()) / PArr[LongestListIdx]->GetTotalCT();
				}
			}
		} while (Steal_Limit > 0.4 && PArr[LongestListIdx]->GetTotalCT()!=0);
		
	}
}


void Scheduler::ChildrenKilling(Process* Parent)
{
	if (Parent)
	{
		if ((!Parent->GetFirstChild()) && (!Parent->GetSecondChild()))
			return;

		if (Parent->GetFirstChild()) //Checks if the parent has first child
		{
			for (int i = 0; i < FCFS_ProcessorsCnt; i++)
			{
				if (PArr[i]->Search(Parent->GetFirstChild())) //Checks if the child is in a ready queue of any FCFS processor
				{
					addToTrm(Parent->GetFirstChild());
					PArr[i]->DeleteProcessAtPosition(Parent->GetFirstChild());
					KilledCount++;
				}
				else if (PArr[i]->getRunning() == Parent->GetFirstChild()) //Checks if the child is running in any FCFS processor
				{
					addToTrm(Parent->GetFirstChild());
					PArr[i]->SetRunning(nullptr);
					PArr[i]->setisbusy(false);
					DecrementRunningCount();
					KilledCount++;
				}
			}
			ChildrenKilling(Parent->GetFirstChild());
			ChildrenKilling(Parent->GetSecondChild());
		}

		if (Parent->GetSecondChild()) //Checks if the parent has second child
		{
			for (int i = 0; i < FCFS_ProcessorsCnt; i++)
			{
				if (PArr[i]->Search(Parent->GetSecondChild())) //Checks if the child is in a ready queue of any FCFS processor
				{
					addToTrm(Parent->GetSecondChild());
					PArr[i]->DeleteProcessAtPosition(Parent->GetSecondChild());
					KilledCount++;
				}
				else if (PArr[i]->getRunning() == Parent->GetSecondChild()) //Checks if the child is running in any FCFS processor
				{
					addToTrm(Parent->GetSecondChild());
					PArr[i]->SetRunning(nullptr);
					PArr[i]->setisbusy(false);
					DecrementRunningCount();
					KilledCount++;
				}
			}
			ChildrenKilling(Parent->GetFirstChild());
			ChildrenKilling(Parent->GetSecondChild());
		}
	}
	return;
}

void Scheduler::IncrementTotalTRT(int trt)
{
	TotalTRT += trt;
}

void Scheduler::IncrementMaxW()
{
	TotalMigFromFCFSToRR++;
}

void Scheduler::IncrementRTF()
{
	TotalMigFromRRToSJF++;
}


void Scheduler::IncrementKilledCount()
{
	KilledCount++;
}

void Scheduler::AddToShortestRdyList(Process*& p)
{
	if (p->GetParent())
	{
		Set_ShortestFCFS();
		PArr[ShortestFCFSListIdx]->AddToRdy(p);
	}
	else
	{
		Set_ShortestListIdx();
		PArr[ShortestListIdx]->AddToRdy(p);
	}
}




