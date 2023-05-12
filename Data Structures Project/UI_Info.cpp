#pragma once
#include "UI_Info.h"
#include "Scheduler.h"
#include <chrono>
#include <thread>
UI_Info::UI_Info(Scheduler* Sptr)
{
	S = Sptr;
	int x;
	cout << "please choose your desired mode" << endl;
	cout << "There are Three Modes:" << endl << "Enter 0 For Interactive Mode" << endl << "Enter 1 For Step - by - step mode" << endl << "Enter 2 For Silent mode" << endl;
	cin >> x;
	switch (x)
	{
	case(0):
		InterfaceMode = Interactive_Mode;
		break;
	case(1):
		InterfaceMode = Step_By_Step_Mode;
		break;
	case(2):
		InterfaceMode = Silent_Mode;
		break;
	default:
		InterfaceMode = Interactive_Mode;
		break;
	}
	string y;
	cout << "please enter your filename " << endl;
	cin >> y;
	FLName = y;
	S->setfilename(FLName);

}
void UI_Info::printInterface(int timestep)
{
	if (InterfaceMode == 0)
		PrintInteractiveMode(timestep);
	else if (InterfaceMode == 1)
		PrintStep_By_StepMode(timestep);
	else
		PrintSilentMode();
}
void UI_Info::PrintInteractiveMode(int timestep)
{
	cout << "current timestep: " << timestep << endl;
	cout << "------------------------- RDY Processes ------------------------- " << endl;
	S->PrintProcessorList();
	cout << "------------------------- BLK Processes ------------------------- " << endl;
	S->PrintBLKList();
	cout << endl << "------------------------- RUN Processes ------------------------- " << endl;
	S->PrintRunningList();
	cout << endl << "------------------------- TRM Processes ------------------------- " << endl;
	S->PrintTRMList();
	cout << endl<<"PRESS ANY KEY TO MOVE TO NEXT STEP !" << endl;
	system("pause");
}

void UI_Info::PrintStep_By_StepMode(int timestep)
{
	cout << "current timestep: " << timestep << endl;
	cout << "------------------------- RDY Processes ------------------------- " << endl;
	S->PrintProcessorList();
	cout << "------------------------- BLK Processes ------------------------- " << endl;
	S->PrintBLKList();
	cout << endl << "------------------------- RUN Processes ------------------------- " << endl;
	S->PrintRunningList();
	cout << endl << "------------------------- TRM Processes ------------------------- " << endl;
	S->PrintTRMList();
	wait();
}

void UI_Info::PrintSilentMode()
{
	if (S->AllIsTerminated())
	{
		cout << "Silent Mode...............      Simulation Starts..." << endl;
		cout << "Simulation ends, Output file Created";
	}
}

void UI_Info::wait()
{
	
		using namespace std::this_thread;     // sleep_for, sleep_until
		using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
		using std::chrono::system_clock;
		sleep_for(100ns);
		sleep_until(system_clock::now() + 1s);
	
}
