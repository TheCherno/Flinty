#pragma once

#include <chrono>

class Timer
{
private:
	typedef std::chrono::high_resolution_clock HighResolutionClock;
	typedef std::chrono::duration<float, std::milli> milliseconds_type;

	std::chrono::time_point<HighResolutionClock> m_Start;
public:
	inline Timer()
	{
		Reset();
	}

	inline void Reset()
	{
		m_Start = HighResolutionClock::now();
	}

	inline float Elapsed()
	{
		return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - m_Start).count() / 1000.0f;
	}

	inline float ElapsedMillis()
	{
		return Elapsed() * 1000.0f;
	}
};
