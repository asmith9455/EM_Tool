#pragma once

#include <chrono>

class Stopwatch
{


public:
	
	typedef std::chrono::high_resolution_clock Clock;

	void start()
	{
		this->epoch = clock.now();
	}

	void stop()
	{
		this->end = clock.now();
	}

	long long miliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - epoch).count();
	}

	long long nanoseconds()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(end - epoch).count();
	}

	long long seconds()
	{
		return std::chrono::duration_cast<std::chrono::seconds>(end - epoch).count();
	}

	long long microseconds()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(end - epoch).count();
	}

	Stopwatch() {}

private:

	Clock clock;
	std::chrono::system_clock::time_point epoch;
	std::chrono::system_clock::time_point end;

};