#include "common/stdafx.h"

#include "kernel/time/timesource.h"

//==============================================================================

namespace engine
{
	//============================================================================

	double CTimeSource::Tick(void)
	{
	 	++m_frameCount;
	 	return m_frameTime;
	}

	//============================================================================

	void CTimeSource::GetTime(uint32* pHours, uint32* pMinutes, double* pSeconds)
	{
		double elapsedTime = m_currentTime;

		if (pHours != NULL)
		{
			*pHours = static_cast<uint32>(elapsedTime/3600.0);
			elapsedTime -= *pHours*3600;
		}

		if (pMinutes != NULL)
		{
			*pMinutes = static_cast<uint32>(elapsedTime/60.0);
			elapsedTime -= *pMinutes*60;
		}

		if (pSeconds != NULL)
		{
			*pSeconds = elapsedTime;
		}
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
