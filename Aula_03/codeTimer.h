#ifndef _CODETIMER_H
#define _CODETIMER_H



#include<iostream>
#include<memory>
#include<chrono>

// Class Timer

class Timer
{
public:
	//Constructor
	Timer();
	// Destractor
	~Timer();
	void Stop();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};


#endif // !_CODETIMER_H