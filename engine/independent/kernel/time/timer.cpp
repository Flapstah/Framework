#include "common/stdafx.h"

#include "kernel/time/timer.h"
#include "kernel/time/realtimeclock.h"

//==============================================================================

namespace engine
{
	//============================================================================

	bool CTimer::Tick(void)
	{
		bool ticked = false;

		if ((!m_paused) && (m_frameCount < m_timeSource.GetFrameCount()))
		{
			m_frameTime = (m_timeSource.GetTickTimePrecise() * m_scale) - m_currentTime;
			m_currentTime += m_frameTime;

			if ((m_maxFrameTime > 0.0) && (m_frameTime > m_maxFrameTime))
			{
				m_frameTime = m_maxFrameTime;
			}

			m_frameCount = m_timeSource.GetFrameCount();
			ticked = true;
		}

		return ticked;
	}

	//============================================================================

	//----------------------------------------------------------------------------
	// The global instance of the game clock
	//----------------------------------------------------------------------------
	CTimer g_gameClock(g_realTimeClock, 1.0, 0.1);

	//============================================================================

	ITimer* GetGameClock(void)
	{
		return &g_gameClock;
	}

	//============================================================================

	ITimer* CreateTimer(ITimeSource& source, double scale, double maxFrameTime)
	{
		return new CTimer(source, scale, maxFrameTime);
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
