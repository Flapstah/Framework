#if !defined(__TIME_H__)
#define __TIME_H__

//==============================================================================

#include "kernel/time/timer.h"
#include "kernel/time/realtimeclock.h"

//==============================================================================

namespace engine
{
	//============================================================================
	// CTime
	//============================================================================
	class CTime
	{
	public:
										CTime(void)										{ Initialise();							}
										~CTime(void)									{ Uninitialise();						}

		IRealTimeClock*	GetRealTimeClock(void) const	{ return s_pRealTimeClock;	}
		ITimer*					GetGameClock(void) const			{ return s_pGameClock;			}
		ITimer*					CreateTimer(ITimeSource& source, double scale, double maxFrameTime) { return new CTimer(source, scale, maxFrameTime);	}

	protected:
		void						Initialise(void);
		void						Uninitialise(void);

	protected:
		static	CRealTimeClock*	s_pRealTimeClock;
		static	CTimer*					s_pGameClock;
	}; // End [class CTime]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__TIME_H__)]
// [EOF]
