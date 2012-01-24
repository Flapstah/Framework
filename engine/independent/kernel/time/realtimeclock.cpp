#include "common/stdafx.h"

#include "kernel/time/realtimeclock.h"

//==============================================================================

namespace engine
{
	//============================================================================

	bool CRealTimeClock::Tick(void)
	{
		PARENT::Tick();

		double currentTime = Platform_GetTimePrecise();
		m_frameTime = currentTime - m_currentTime;
		m_currentTime = currentTime;

		return true;
	}

	//============================================================================

	//----------------------------------------------------------------------------
	// The global instance of the real time clock
	//----------------------------------------------------------------------------
	CRealTimeClock g_realTimeClock;

	//============================================================================

	IRealTimeClock* GetRealTimeClock(void)
	{
		return &g_realTimeClock;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
