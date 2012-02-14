#include "common/stdafx.h"

#include "kernel/time/time.h"

//==============================================================================

namespace engine
{
	//============================================================================

	void CTime::Sleep(uint32 microseconds) const
	{
		uint32 milliseconds = microseconds/1000;
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
