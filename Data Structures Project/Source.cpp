#pragma once 
using namespace std;
#include <iostream>
#include "Scheduler.h"
#include "UI_Info.h"
int main()
{
	//Scheduler* S = new Scheduler;
	Scheduler* S=new Scheduler;
	S->Simulation();
	system("pause");
	delete S;
	S = NULL;
	//Process* p1=new Process(1, 1, 10);
	//Process* p2=new Process(1, 2, 10);
	//S->simulation();
	//system("pause");
	//delete S;
	//S = NULL;


	//Process* p1=new Process(1, 1, 10);
	//
	//Process* p2 = new Process(1, 2, 10);
	//Process* p3=new Process(1, 3, 10);
	//Process* p4=new Process(1, 4, 10);
	//Process* p5=new Process(1, 5, 10);
	//Process* p6=new Process(1, 6, 10);
	//Process* p7=new Process(1, 7, 10);
	//Process* p8 = new Process(1, 8, 10);
	//Process* p9 = new Process(1, 9, 10);
	//p1->AddChild(p2);
	//p1->AddChild(p3);
	//S->addtoparentlist(p1);
	//p2->AddChild(p4);
	//p2->AddChild(p5);
	//S->addtoparentlist(p2);
	//p3->AddChild(p6);
	//p3->AddChild(p7);
	//S->addtoparentlist(p3);
	//p4->AddChild(p8);
	//p4->AddChild(p9);
	//S->addtoparentlist(p4);
	//S->addToTrm(p1);
	//S->ParentKilling(p1);
	////S->AddChildrenToTrm(p1);
	//S->PrintTRMList();
	
	//cout << *p1 << " " << *p1->GetFirstChild() << " " << *p1->GetSecondChild();
	//cout << *p1 << " " << *p1->GetFirstChild() << " " << *p1->GetSecondChild();

	return 0;
}