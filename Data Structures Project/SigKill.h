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
	SIGKILL(int Process_ID, int Kill_Time)
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
	void DecrementKillTime()
	{
		if (KillTime > 0)
			KillTime--;
	}
};
