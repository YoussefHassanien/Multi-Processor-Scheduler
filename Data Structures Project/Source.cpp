#pragma once 
using namespace std;
#include <iostream>
#include "Scheduler.h"
#include "UI_Info.h"
int main()
{
<<<<<<< HEAD
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
=======
	Scheduler* S=new Scheduler;
	S->simulation();
	system("pause");
	delete S;
	S = NULL;
	//Process* p1=new Process(1, 1, 10);
	//Process* p2=new Process(1, 2, 10);
	//Process* p3=new Process(1, 3, 10);
	//Process* p4=new Process(1, 4, 10);
	//Process* p5=new Process(1, 5, 10);
	//Process* p6=new Process(1, 6, 10);
	//Process* p7=new Process(1, 7, 10);
	//p1->AddChildren(p2, p3);
	//p2->AddChildren(p4, p5);
	//p3->AddChildren(p6, p7);
	//p1->GetChildrenTree()->Delete(p6);
	//p1->GetChildrenTree()->Delete(p7);
	//p1->GetChildrenTree()->Print();
>>>>>>> f9fd989a6981ec1623eb17254de2d98bd59504ad
	//cout << endl;
	//p2->GetChildsTree()->Print();
	//cout << endl;
	//p3->GetChildsTree()->Print();
	return 0;
}