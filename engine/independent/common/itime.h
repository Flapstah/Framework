#if !defined(__ITIME_H__)
#define __ITIME_H__

//==============================================================================

#include "common/types.h"

//==============================================================================

namespace engine
{
	//============================================================================
	// ITimeSource
	//============================================================================
	struct ITimeSource
	{
		virtual	bool		Tick(void) = 0;

		virtual	float		GetTickTime(void) const = 0;
		virtual	double	GetTickTimePrecise(void) const = 0;

		virtual	float		GetFrameTime(void) const = 0;
		virtual	double	GetFrameTimePrecise(void) const = 0;

		virtual	uint32	GetFrameCount(void) const = 0;

		virtual	void		AddReference(void) = 0;
		virtual	uint32	Release(void) = 0;
	}; // End [struct ITimeSource]

	//============================================================================
	// IRealTimeClock
	//============================================================================
	struct IRealTimeClock : virtual public ITimeSource 
	{
		virtual	float		GetRealTime(void) const = 0;
		virtual	double	GetRealTimePrecise(void) const = 0;

		virtual const char*	GetLocalDateString(void) const = 0;
		virtual const char*	GetLocalTimeString(void) const = 0;
	}; // End [struct IRealTimeClock : public ITimeSource]

	//============================================================================
	// ITimer
	//============================================================================
	struct ITimer : virtual public ITimeSource
	{
		virtual void		SetScale(double scale) = 0;
		virtual double	GetScale(void) const = 0;

		virtual void		Pause(bool pause) = 0;
		virtual bool		IsPaused(void) = 0;

		virtual void		Reset(void) = 0;
	}; // End [struct ITimer : public ITimeSource]

	//----------------------------------------------------------------------------
	// Returns the real time clock
	//----------------------------------------------------------------------------
	IRealTimeClock* GetRealTimeClock(void);

	//----------------------------------------------------------------------------
	// Returns the game clock
	//
	// Use the game clock as the root of all timers (rather than the system clock)
	// as it's current time count will be elapsed *game* time, not *real* time.
	//----------------------------------------------------------------------------
	ITimer* GetGameClock(void);

	//----------------------------------------------------------------------------
	// Creates a general purpose timer
	//----------------------------------------------------------------------------
	ITimer* CreateTimer(ITimeSource& source, double scale, double maxFrameTime);

	//============================================================================
} // End [namespace engine]

//==============================================================================

#endif // End [!defined(__ITIME_H__)]
// [EOF]
