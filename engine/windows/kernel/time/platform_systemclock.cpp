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
		m_secondsPerTick = 1.0 / frequency.QuadPart;

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
		double currentTime = time.QuadPart * m_secondsPerTick;

		return currentTime;
	}

	//============================================================================

	const char* CRealTimeClock::Platform_GetLocalDateString(void) const
	{
		::time_t absoluteTime;
		::time(&absoluteTime);

		::tm* pLocalTime;
		pLocalTime = ::localtime(&absoluteTime);

		memset(m_localDate, 0, REAL_TIME_CLOCK_DATE_BUFFER_SIZE);
		::strftime(m_localDate, REAL_TIME_CLOCK_DATE_BUFFER_SIZE, "%d/%m/%Y", pLocalTime);
		return m_localDate;
	}

	//============================================================================

	const char* CRealTimeClock::Platform_GetLocalTimeString(void) const
	{
		::time_t absoluteTime;
		::time(&absoluteTime);

		::tm* pLocalTime;
		pLocalTime = ::localtime(&absoluteTime);

		memset(m_localTime, 0, REAL_TIME_CLOCK_TIME_BUFFER_SIZE);
		::strftime(m_localTime, REAL_TIME_CLOCK_TIME_BUFFER_SIZE, "%H:%M:%S", pLocalTime);
		return m_localTime;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
