#include "common/stdafx.h"

#include "kernel/time/realtimeclock.h"

//==============================================================================

namespace engine
{
	//============================================================================

	void CRealTimeClock::Platform_Initialise(void)
	{
		LARGE_INTEGER frequency;

		::QueryPerformanceFrequency(&frequency);
		m_ticksPerSecond = frequency.QuadPart;

		Tick();
		m_frameTime = 0.0;
	}

	//============================================================================

	void CRealTimeClock::Platform_Uninitialise(void)
	{
		// Nothing to do
	}

	//============================================================================

	double CRealTimeClock::Platform_GetTimePrecise(void) const
	{
		LARGE_INTEGER time;

		::QueryPerformanceCounter(&time);
		double currentTime = time.QuadPart / m_ticksPerSecond;

		return currentTime;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
