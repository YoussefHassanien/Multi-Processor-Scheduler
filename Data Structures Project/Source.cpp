#pragma once 
using namespace std;
#include <iostream>
#include "Scheduler.h"
#include "UI_Info.h"
int main()
{
	//Scheduler* S=new Scheduler;
	//S->simulation();
	//system("pause");
	//delete S;
	//S = NULL;
	Process* p1=new Process(1, 1, 10);
	Process* p2=new Process(1, 2, 10);
	Process* p3=new Process(1, 3, 10);
	Process* p4=new Process(1, 4, 10);
	Process* p5=new Process(1, 5, 10);
	Process* p6=new Process(1, 6, 10);
	Process* p7=new Process(1, 7, 10);
	p1->AddChild(p2);
	p1->AddChild(p3);
	cout << *p1 << " " << *p1->GetFirstChild() << " " << *p1->GetSecondChild();
	return 0;
}