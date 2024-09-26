#include"codeTimer.h"

// Constructor
Timer::Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
		std::cout << "Timer Started!!" << std::endl;
	}
// DesContructor
	Timer::~Timer() {
		Stop();
	}

void Timer::Stop() {
	auto endTimepoint = std::chrono::high_resolution_clock::now();
	std::cout << "Timer Stoped!!" << std::endl;

	auto duration_single_thread = std::chrono::duration_cast<std::chrono::microseconds>(endTimepoint - m_StartTimepoint);

	// Display timing results
	std::cout << "Single-threaded image processing time: " << duration_single_thread.count() << " millis" << std::endl;

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
	auto duration = end - start;
	double ms = duration * 0.001;

	std::cout << duration << "us(" << ms << "ms)\n";
	std::cout << ms << "us\n";
	}
