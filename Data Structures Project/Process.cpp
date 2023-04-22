#include "Process.h"

Process::Process(int at, int id, int ct, int n)
{
	SetAT(at);
	SetID(id);
	SetCT(ct);
	SetN(n);
	if (n)
	{
		IOArr = new IO*[N];
	}
	ChildPtr = NULL;
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
void Process::SetChildPtr(Process* Ptr)
{
	ChildPtr = Ptr;
}
void Process::DecrementCT()
{
	CT--;
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
Process* Process::GetChildPtr()
{
	return ChildPtr;
}
bool Process::GetOrph()
{
	return Orph;
}
void Process::PrintProcessInfo()
{
	cout << "TT" << " " << " " << " " << " " << " " << "PID" << " " << " " << " " << " " << " " << "AT" << " " << " " << " " << " " << " " << "CT" << " " << " " << " " << " " << " " << "IO_D" << " " << " " << " " << " " << " " << "WT" << " " << " " << " " << " " << " " << "RT" << " " << " " << " " << " " << " " << "TRT" << endl;
	cout << TT << " " << " " << " " << " " << " " << ID << " " << " " << " " << " " << " " << AT << " " << " " << " " << " " << " " << CT << " " << " " << " " << " " << " " << IOArr[0]->GetDuration() << " " << " " << " " << " " << " " << WT << " " << " " << " " << " " << " " << RT << " " << " " << " " << " " << " " << TRT << endl;
}
void Process::AddIO(IO *Arr[])
{
	for (int i = 0; i < N; i++)
	{
		IOArr[i] = Arr[i];
	}
}
void Process::AddChild(int t, int rct)
{
	ChildPtr = new Process(t, s->getChildID(), rct, 0);
	s->incrementChildID();
}
Process::~Process()
{
	for (int i = 0; i < N; i++)
	{
		delete IOArr;
	}
	IOArr = NULL;
	delete ChildPtr;
	ChildPtr = NULL;
}

ostream& operator<<(ostream& output, Process& p)
{
	output << p.ID;
	return output;
}
