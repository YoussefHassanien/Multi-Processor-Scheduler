#pragma once
#include "UI_Info.h"
#include "Scheduler.h"
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
void UI_Info::PrintInteractiveMode()
{
	cout << "current timestep: " << S->getTimeStep() << endl;
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
