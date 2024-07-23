/*
* 
*/

#include "HighPerfomanceClock.hpp"

Clock::Clock() :
	deltaTime(0),
	totalTime(0) {
	t0 = clock::now();
}

void Clock::Tick() {
	auto t1 = clock::now();
	deltaTime = t1 - t0;
	totalTime += deltaTime;
	t0 = t1;
}

void Clock::Reset() {
	t0 = clock::now();
	deltaTime = clock::duration();
	totalTime = clock::duration();
}

// !ignore S5276 warning by long long to double conversion
double Clock::GetDeltaSeconds() const {
	return deltaTime.count() * 1e-9;
}

double Clock::GetDeltaMilliseconds() const {
	return deltaTime.count() * 1e-6;
}

double Clock::GetDeltaMicroseconds() const {
	return deltaTime.count() * 1e-3;
}

double Clock::GetDeltaNanoseconds() const {
	return deltaTime.count() * 1e+0;
}

double Clock::GetTotalSeconds() const {
	return totalTime.count() * 1e-9;
}

double Clock::GetTotalMilliseconds() const {
	return totalTime.count() * 1e-6;
}

double Clock::GetTotalMicroseconds() const {
	return totalTime.count() * 1e-3;
}

double Clock::GetTotalNanoseconds() const {
	return totalTime.count() * 1e+0;
}