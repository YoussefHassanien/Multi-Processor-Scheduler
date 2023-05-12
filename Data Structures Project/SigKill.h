#pragma once
#include <iostream>
using namespace std;
class SIGKILL
{
private:
	int ProcessID;
	int KillTime;      
public:
	//Constructor
	SIGKILL(int Kill_Time, int Process_ID)
	{
		ProcessID = Process_ID;
		KillTime = Kill_Time;
	}
	//Getter for the ID
	int getID()
	{
		return ProcessID;
	}
	//Getter for the kill time
	int getTime()
	{
		return KillTime;
	}
};
