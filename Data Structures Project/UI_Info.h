#ifndef UI_INFO_H
#define UI_INFO_H
#include <iostream>
using namespace std;
#pragma once
class Scheduler;
//User Interface information file.

enum GUI_MODE	//Graphical user interface mode
{
	Interactive_Mode, //index 0
	Step_By_Step_Mode, // index 1
	Silent_Mode, //index 2
};


class UI_Info	//User Interface Info.
{
public:
	GUI_MODE InterfaceMode;
	Scheduler* S;
	string FLName;
	UI_Info(Scheduler* Sptr);
	void printInterface(int timestep, int blkcnt, int termcnt);
	void PrintInteractiveMode(int timestep, int blkcnt, int termcnt);
	void PrintStep_By_StepMode(int timestep, int blkcnt, int termcnt);
	void PrintSilentMode();
	void wait();
};

#endif