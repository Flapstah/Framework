#if !defined(__TIMER_H__)
#define __TIMER_H__

//==============================================================================

#include "kernel/time/timesource.h"

//==============================================================================

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4250) // 'class1' : inherits 'class2::member' via dominance
#endif // defined(_MSC_VER)

//==============================================================================

namespace engine
{
	//============================================================================
	// CTimer
	//============================================================================
	class CTimer : virtual public ITimer, public CTimeSource
	{
	protected:
		typedef CTimeSource PARENT;

	public:
										CTimer(ITimeSource& source, double scale, double maxFrameTime)
											: m_timeSource(source), m_scale(scale), m_maxFrameTime(maxFrameTime)
																								{	m_timeSource.AddReference();							}
		virtual					~CTimer(void)								{ m_timeSource.Release();										}

		// ITimeSource
		virtual	bool		Tick(void);
		// ~ITimeSource

		// ITimer
		virtual	void		SetScale(double scale)			{	m_scale = scale;													}
		virtual	double	GetScale(void) const				{	return m_scale;														}

		virtual	void		Pause(bool pause)						{ m_paused = true; m_frameTime = 0.0;				}
		virtual	bool		IsPaused(void)							{	return m_paused;													}

		virtual	void		Reset(void)									{ m_currentTime = m_frameTime = 0.0;				}
		// ~ITimer

	protected:
		ITimeSource&	m_timeSource;
		double				m_scale;
		double				m_maxFrameTime;
		bool					m_paused;
	}; // End [struct CTimer : public ITimeSource]

	//============================================================================
} // End [namespace engine]

//==============================================================================

#if defined(_MSC_VER)
#pragma warning(pop)
#endif // defined(_MSC_VER)

//==============================================================================
#endif // End [!defined(__TIMER_H__)]
// [EOF]
