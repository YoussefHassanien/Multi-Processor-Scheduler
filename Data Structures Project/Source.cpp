#pragma once 
using namespace std;
#include <iostream>
#include "Scheduler.h"
#include "UI_Info.h"
int main()
{
	Scheduler* S=new Scheduler;
	S->simulation();
	system("pause");
	delete S;
	S = NULL;

	
	return 0;
}