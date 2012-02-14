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
										CTime(void) : m_gameClock(m_realTimeClock, 1.0, 0.1)	{}
										~CTime(void)																					{}

		// ITime
		virtual IRealTimeClock*	GetRealTimeClock(void);
		virtual ITimer*					GetGameClock(void);
		virtual ITimer*					CreateTimer(ITimeSource& source, double scale, double maxFrameTime);
		virtual void						Sleep(uint32 microseconds) const;
		// ~ITime

	protected:
		CRealTimeClock	m_realTimeClock;
		CTimer					m_gameClock;
	}; // End [class CTime]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__TIME_H__)]
// [EOF]
