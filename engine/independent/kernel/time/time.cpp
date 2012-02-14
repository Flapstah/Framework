#include "common/stdafx.h"

#include <new>

#include "kernel/time/time.h"
#include "kernel/time/timer.h"

//==============================================================================

namespace engine
{
	//============================================================================

	static char g_timeMemory[sizeof(CTime)];	// memory for global CTime
	static CTime* g_pTime;										// global pointer to CTime

	//============================================================================
	// CTimeFactory
	//============================================================================
	class CTimeFactory
	{
		public:
			CTimeFactory(void) { g_pTime = ::new(static_cast<void*>(g_timeMemory)) CTime(); }
			~CTimeFactory(void) { g_pTime->~CTime(); }
	};

	//============================================================================

	static CTimeFactory g_timeFactory;				// factory class to construct CTime

	//============================================================================

	ITime* GetTime(void)
	{
		return g_pTime;
	}

	//============================================================================

	IRealTimeClock* CTime::GetRealTimeClock(void)
	{
		return &m_realTimeClock;
	}

	//============================================================================

	ITimer* CTime::GetGameClock(void)
	{
		return &m_gameClock;
	}

	//============================================================================

	ITimer* CTime::CreateTimer(ITimeSource& source, double scale, double maxFrameTime)
	{
		return new CTimer(source, scale, maxFrameTime);
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
