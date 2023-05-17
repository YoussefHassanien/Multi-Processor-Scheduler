#pragma once
#include <iostream>
class IO
{
public:
	int Request, Duration;

public:
	IO(int IO_R = 0, int IO_D = 0);           //Default constructor
	void SetRequest(int io_r);                //Setter for the request time
	void SetDuration(int io_d);               //Setter for the duration
	int GetRequest();                         //Getter for the request time
	int GetDuration();                        //Getter for the duration 
	~IO();                                    //Destructor

};
