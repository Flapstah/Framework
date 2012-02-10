#include "common/stdafx.h"
#include <sys/time.h>

#include "common/types.h"
#include "kernel/time/realtimeclock.h"

//==============================================================================

static const uint64 usec_per_sec = 1000000;
static const uint64 usec_per_msec = 1000;

//==============================================================================

namespace engine
{
	//============================================================================

	void CRealTimeClock::Platform_Initialise(void)
	{
		m_ticksPerSecond = usec_per_sec;

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
		::timeval time;

		::gettimeofday(&time, NULL);
		double currentTime = (time.tv_usec / m_ticksPerSecond) + time.tv_sec;

		return currentTime;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
