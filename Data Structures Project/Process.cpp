#include "Process.h"

Process::Process(int at, int id, int ct, int n)
{
	SetAT(at);
	SetID(id);
	SetCT(ct);
	SetN(n);
	IOqueue = new LinkedQueue<IO*>;
	ChildsTree->Insert(this);
	Orph = false;
	S = New;
	
	
	// Termination time should be sent when the process moves from the running queue to the termination queue inside a processor
	// Response time should be calculated when the process moves from the ready queue to the running queue inside a processor
	// Turnaround duration should be calculated when the termination time arrives
	// Waiting time should be calculated when the turnaround duration is calculated (when termination time arrives) 
}
void Process::SetID(int id)
{
	ID = id;
}
void Process::SetAT(int at)
{
	AT = at;
}
void Process::SetRT(int CPU_First_AT)
{
	RT = CPU_First_AT - AT;
}
void Process::SetCT(int ct)
{
	CT = ct;
}
void Process::SetTT(int tt)
{
	TT = tt;
	TRT = tt - AT;
	WT = (tt - AT) - CT;
}
void Process::SetTRT(int trt)
{
	TRT = trt;
}
void Process::SetWT(int wt)
{
	WT = wt;
}
void Process::SetN(int n)
{
	N = n;
}
void Process::DecrementCT()
{
	CT--;
}

void Process::IncrementRunningFor()
{
	RunningFor++;
}

void Process::SetS(int s)
{
	switch (s)
	{
	default:New;
		S = New;
		break;
	case(1):
		S = Rdy;
		break;
	case(2):
		S = Run;
		break;
	case(3):
		S = Blck;
		break;
	case(4):
		S = Term;
		break;

	}
}
void Process::SetOrph(bool orph)
{
	Orph = orph;
}
int Process::GetID()
{
	return ID;
}
int Process::GetAT()
{
	return AT;
}
int Process::GetRT()
{
	return RT;
}
int Process::GetCT()
{
	return CT;
}
int Process::GetTT()
{
	return TT;
}
int Process::GetTRT()
{
	return TRT;
}
int Process::GetWT()
{
	return WT;
}
int Process::GetN()
{
	return N;
}
int Process::GetRunningFor()
{
	return RunningFor;
}
bool Process::GetOrph()
{
	return Orph;
}
void Process::PrintProcessInfo()
{
	cout << "TT" << " " << " " << " " << " " << " " << "PID" << " " << " " << " " << " " << " " << "AT" << " " << " " << " " << " " << " " << "CT" << " " << " " << " " << " " << " " << "IO_D" << " " << " " << " " << " " << " " << "WT" << " " << " " << " " << " " << " " << "RT" << " " << " " << " " << " " << " " << "TRT" << endl;
	cout << TT << " " << " " << " " << " " << " " << ID << " " << " " << " " << " " << " " << AT << " " << " " << " " << " " << " " << CT << " " << " " << " " << " " << " " << " hena feeh IOD" << " " << " " << " " << " " << " " << WT << " " << " " << " " << " " << " " << RT << " " << " " << " " << " " << " " << TRT << endl;
}

void Process::AddIO(LinkedQueue<IO*>* ioq)
{
	IOqueue = ioq;
}

void Process::GetFirstIO(IO*& ioTemp)
{
	IOqueue->peek(ioTemp);
}

BinaryTree<Process*>* Process::GetChildsTree()
{
	return ChildsTree;
}

bool Process::CheckIO_D()
{
	IO* tempIO;
	IOqueue->peek(tempIO);
	if (tempIO->Duration==0)
	{
		IOqueue->dequeue(tempIO);
		return true;
	}
	else
	{
		tempIO->Duration--;
		return false;
	}
}

void Process::AddChilds(Process*child1,Process*child2)
{
	ChildsTree->Insert(child1);
	ChildsTree->Insert(child2);
}

Process::~Process()
{
	delete IOqueue;
	IOqueue = nullptr;
	delete ChildsTree;
	ChildsTree = nullptr;
}

ostream& operator<<(ostream& output, Process& p)
{
	output << p.ID;
	return output;
}


bool operator==(Process& p1, Process& p2)
{
	return (p1.GetID()==p2.GetID()) ;
}

bool operator==(int value, Process& p)
{
	return (value==p.GetID());
}
