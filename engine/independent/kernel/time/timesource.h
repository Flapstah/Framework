#if !defined(__TIMESOURCE_H__)
#define __TIMESOURCE_H__

//==============================================================================

#include "common/itime.h"

//==============================================================================

namespace engine
{
	//============================================================================
	// CTimeSource
	//============================================================================
	class CTimeSource : virtual public ITimeSource
	{
	public:
		CTimeSource(void)
			: m_currentTime(0.0), m_frameTime(0.0), m_frameCount(0), m_referenceCount(0)
																										{																						}
		virtual					~CTimeSource(void)							{	assert(m_referenceCount == 0);						}

		// ITimeSource
		virtual	bool		Tick(void) = 0;

		virtual	float		GetTickTime(void) const					{ return static_cast<float>(m_currentTime);	}
		virtual	double	GetTickTimePrecise(void) const	{	return m_currentTime;											}

		virtual	float		GetFrameTime(void) const				{ return static_cast<float>(m_frameTime);		}
		virtual	double	GetFrameTimePrecise(void) const	{	return m_frameTime;												}

		virtual	uint32	GetFrameCount(void) const				{ return m_frameCount;											}

		virtual	void		AddReference(void)							{ ++m_referenceCount;												}
		virtual	uint32	Release(void)										{ return --m_referenceCount;								}
		// ~ITimeSource

	protected:
		double m_currentTime;
		double m_frameTime;
		uint32 m_frameCount;
		uint32 m_referenceCount;
	}; // End [class CTimeSource : public ITimeSource]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__TIMESOURCE_H__)]
// [EOF]
