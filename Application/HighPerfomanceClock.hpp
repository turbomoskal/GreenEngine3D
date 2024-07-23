/*
*	High Perfomance Clock module
*/

#pragma once
#include "LangHeaders.hpp"

class Clock
{
private:
	using clock = std::chrono::high_resolution_clock;

	clock::time_point t0;
	clock::duration deltaTime;
	clock::duration totalTime;
public:
	Clock();

	//! Tick the HPC.
	//! Use it defore reading deltaTime for the first time
	//! Once per frame
	//! Use get to return time between ticks
	void Tick();

	void Reset();

	double GetDeltaSeconds() const;
	double GetDeltaMilliseconds() const;
	double GetDeltaMicroseconds() const;
	double GetDeltaNanoseconds() const;

	double GetTotalSeconds() const;
	double GetTotalMilliseconds() const;
	double GetTotalMicroseconds() const;
	double GetTotalNanoseconds() const;
};