#include "common/stdafx.h"

#include "kernel/time/timer.h"

//==============================================================================

namespace engine
{
	//============================================================================

	double CTimer::Tick(void)
	{
		if ((!m_paused) && (m_timeSourceFrameCount < m_timeSource.GetFrameCount()))
		{
			PARENT::Tick();

			m_frameTime = (m_timeSource.GetTickTime() * m_scale) - m_currentTime;
			m_currentTime += m_frameTime;

			if ((m_maxFrameTime > 0.0) && (m_frameTime > m_maxFrameTime))
			{
				m_frameTime = m_maxFrameTime;
			}

			m_timeSourceFrameCount = m_timeSource.GetFrameCount();
		}
		else
		{
			printf("CTimer::Tick() called too many times per frame\n");
		}

		return m_frameTime;
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
