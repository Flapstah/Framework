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
												CRealTimeClock(void)						{	Platform_Initialise();																}
		virtual							~CRealTimeClock(void)						{	Platform_Uninitialise();															}

		// ITimeSource
		virtual	bool				Tick(void);
		// ~ITimeSource

		// IRealTimeClock
		virtual	float				GetRealTime(void) const					{ return static_cast<float>(Platform_GetTimePrecise());	}
		virtual	double			GetRealTimePrecise(void) const	{	return Platform_GetTimePrecise();											}

		virtual const char*	GetLocalDateString(void) const;
		virtual const char*	GetLocalTimeString(void) const;
		// ~IRealTimeClock

	protected:
						void				Platform_Initialise(void);
						void				Platform_Uninitialise(void);
						double			Platform_GetTimePrecise(void) const;
						const char*	Platform_GetLocalDateString(void) const;
						const char*	Platform_GetLocalTimeString(void) const;

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
