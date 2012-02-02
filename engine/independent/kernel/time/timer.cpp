#include "common/stdafx.h"

#include "kernel/time/timer.h"

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
} // End [namespace engine]

//==============================================================================
// [EOF]
