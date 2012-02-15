#include "common/stdafx.h"

#include "kernel/time/time.h"

//==============================================================================

namespace engine
{
	//============================================================================

	void CTime::Sleep(uint32 microseconds) const
	{
		// round up to the nearest 1/2 millisecond
		uint32 milliseconds = (microseconds+500)/1000;
		if ((milliseconds == 0) && (microseconds > 0))
		{
			milliseconds = 0;
		}

		::Sleep(milliseconds);
	}

	//============================================================================
} // End [namespace engine]

//==============================================================================
// [EOF]
