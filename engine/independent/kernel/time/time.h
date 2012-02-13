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
	class CTime : public ITime
	{
	public:
										CTime(void)										{ Initialise();							}
										~CTime(void)									{ Uninitialise();						}

		// ITime
		virtual IRealTimeClock*	GetRealTimeClock(void) const;
		virtual ITimer*					GetGameClock(void) const;
		virtual ITimer*					CreateTimer(ITimeSource& source, double scale, double maxFrameTime);
		virtual void						Sleep(uint32 milliseconds)		{ Platform_Sleep(milliseconds); }
		// ~ITime

	protected:
		void						Initialise(void);
		void						Uninitialise(void);
		void						Platform_Sleep(uint32 milliseconds);

	protected:
		static	CRealTimeClock*	s_pRealTimeClock;
		static	CTimer*					s_pGameClock;
	}; // End [class CTime]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__TIME_H__)]
// [EOF]
