#include "common/stdafx.h"

#include "kernel/time/realtimeclock.h"

//==============================================================================

namespace engine
{
	//============================================================================

	double CRealTimeClock::Tick(void)
	{
		PARENT::Tick();

		double currentTime = GetTime();
		m_frameTime = currentTime - m_currentTime;
		m_currentTime = currentTime;

		return m_frameTime;
	}

	//============================================================================

	const char* CRealTimeClock::GetDateString(void) const
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

	const char* CRealTimeClock::GetTimeString(void) const
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
