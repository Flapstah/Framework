#if !defined(__PLATFORM_STDAFX_H__)
#define __PLATFORM_STDAFX_H__

//==============================================================================

#include <signal.h>

//==============================================================================

#define DEBUG_BREAK raise(SIGTRAP)
#define SLEEP(_milliseconds_) { ::usleep(_milliseconds_ * 1000); }

//==============================================================================

#endif // End [!defined(__PLATFORM_STDAFX_H__)]
// [EOF]
