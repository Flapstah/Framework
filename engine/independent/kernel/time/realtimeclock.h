#if !defined(__REALTIMECLOCK_H__)
#define __REALTIMECLOCK_H__

//==============================================================================

#include "kernel/time/timesource.h"

//==============================================================================

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4250) // 'class1' : inherits 'class2::member' via dominance
#endif // defined(_MSC_VER)

//==============================================================================

#define REAL_TIME_CLOCK_DATE_BUFFER_SIZE (12)
#define REAL_TIME_CLOCK_TIME_BUFFER_SIZE (12)

//==============================================================================

namespace engine
{
	//============================================================================
	// CRealTimeClock
	//============================================================================
	class CRealTimeClock : public virtual IRealTimeClock, public CTimeSource
	{
		typedef CTimeSource PARENT;

	public:
												CRealTimeClock(void)						{	Initialise();			}
		virtual							~CRealTimeClock(void)						{	Uninitialise();		}

		// ITimeSource
		virtual	double			Tick(void);
		// ~ITimeSource

		// IRealTimeClock
		virtual	double			GetRealTime(void) const					{	return GetTime();	}

		virtual const char*	GetDateString(void) const;
		virtual const char*	GetTimeString(void) const;
		// ~IRealTimeClock

	protected:
						void				Initialise(void);
						void				Uninitialise(void);
						double			GetTime(void) const;
						const char*	GetLocalDateString(void) const;
						const char*	GetLocalTimeString(void) const;

	protected:
						double	m_ticksPerSecond;
		mutable char		m_localDate[REAL_TIME_CLOCK_DATE_BUFFER_SIZE];
		mutable char		m_localTime[REAL_TIME_CLOCK_TIME_BUFFER_SIZE];
	}; // End [class CRealTimeClock : public IRealTimeClock]

	//============================================================================
} // End [namespace engine]

//==============================================================================

#if defined(_MSC_VER)
#pragma warning(pop)
#endif // defined(_MSC_VER)

//==============================================================================
#endif // End [!defined(__REALTIMECLOCK_H__)]
// [EOF]
