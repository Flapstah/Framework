#include "common/stdafx.h"

#include <new>

#include "kernel/time/time.h"
#include "kernel/time/timer.h"

//==============================================================================

namespace engine
{
	//============================================================================
	
	static char g_realTimeClockMemory[sizeof(CRealTimeClock)];
	static char g_gameClockMemory[sizeof(CTimer)];

	CRealTimeClock* CTime::s_pRealTimeClock = NULL;
	CTimer* CTime::s_pGameClock = NULL;

	static CTime g_Time;

	//============================================================================

	void CTime::Initialise(void)
	{
		// Use placement new to construct the real-time and game clocks
		if (s_pRealTimeClock == NULL)
		{
			s_pRealTimeClock = ::new(static_cast<void*>(g_realTimeClockMemory)) CRealTimeClock();
		}

		if (s_pGameClock == NULL)
		{
			s_pGameClock = ::new(static_cast<void*>(g_gameClockMemory)) CTimer(*s_pRealTimeClock, 1.0, 0.1);
		}
	}

	//============================================================================

	void CTime::Uninitialise(void)
	{
		// No need to call delete as these were allocated with placement new (but
		// the destructors still need to be called, so are done explicitly here)
		if (s_pGameClock != NULL)
		{
			s_pGameClock->~CTimer();
			s_pGameClock = NULL;
		}

		if (s_pRealTimeClock != NULL)
		{
			s_pRealTimeClock->~CRealTimeClock();
			s_pRealTimeClock = NULL;
		}
	}

	//============================================================================

	IRealTimeClock* GetRealTimeClock(void)
	{
		return g_Time.GetRealTimeClock();
	}

	//============================================================================

	ITimer* GetGameClock(void)
	{
		return g_Time.GetGameClock();
	}

	//============================================================================

	ITimer* CreateTimer(ITimeSource& source, double scale, double maxFrameTime)
	{
		return g_Time.CreateTimer(source, scale, maxFrameTime);
	}

	//============================================================================

	void Sleep(uint32 milliseconds)
	{
		return g_Time.Sleep(milliseconds);
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
