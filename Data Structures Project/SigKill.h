#pragma once
#include <iostream>
using namespace std;
class SIGKILL
{
private:
	int Process_ID;
	int Kill_Time;
public:
	//Constructor
	SIGKILL(int Process_ID, int Kill_Time)
	{
		Process_ID = this->Process_ID;
		Kill_Time = this->Kill_Time;
	}
	//Getter for the ID
	int getID()
	{
		return Process_ID;
	}
	//Getter for the kill time
	int getTime()
	{
		return Kill_Time;
	}
};
