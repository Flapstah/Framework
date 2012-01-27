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
		m_secondsPerTick = usec_per_sec;

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
		double currentTime = time.tv_usec + (time.tv_sec * m_secondsPerTick);

		return currentTime;
	}

	//============================================================================

	TCHAR* CRealTimeClock::Platform_GetLocalDateString(void) const
	{
		::time_t absoluteTime;
		::time(&absoluteTime);

		::tm localTime;
		::localtime_s(&localTime, &absoluteTime);

		memset(m_localDate, 0, sizeof(TCHAR) * REAL_TIME_CLOCK_DATE_BUFFER_SIZE);
		::_tcsftime(m_localDate, REAL_TIME_CLOCK_DATE_BUFFER_SIZE, _TEXT("%d/%m/%Y"), &localTime);
		return m_localDate;
	}

	//============================================================================

	TCHAR* CRealTimeClock::Platform_GetLocalTimeString(void) const
	{
		::time_t absoluteTime;
		::time(&absoluteTime);

		::tm localTime;
		::localtime_s(&localTime, &absoluteTime);

		memset(m_localTime, 0, sizeof(TCHAR) * REAL_TIME_CLOCK_TIME_BUFFER_SIZE);
		::_tcsftime(m_localTime, REAL_TIME_CLOCK_TIME_BUFFER_SIZE, _TEXT("%H:%M:%S"), &localTime);
		return m_localTime;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
