#include "IO.h"


//Default constructor 
IO::IO(int IO_R, int IO_D)
{
	Request = IO_R;
	Duration = IO_D;
}

//Setter for the request time
void IO::SetRequest(int io_r)
{
	Request = io_r;
}

//Setter for the duration
void IO::SetDuration(int io_d)
{
	Duration = io_d;
}

//Getter for the request time
int IO::GetRequest()
{
	return Request;
}

//Getter for the duration
int IO::GetDuration()
{
	return Duration;
}

void IO::DecrementIO_R()
{
	Request--;
}

//Destructor
IO::~IO()
{

}
