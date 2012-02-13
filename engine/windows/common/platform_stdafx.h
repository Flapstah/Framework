#if !defined(__PLATFORM_STDAFX_H__)
#define __PLATFORM_STDAFX_H__

//==============================================================================

#include "common/targetver.h"
#include <windows.h>

//==============================================================================

#if defined(GetCurrentTime)
#undef GetCurrentTime
#endif

#define DEBUG_BREAK DebugBreak()

//==============================================================================

#endif // End [!defined(__PLATFORM_STDAFX_H__)]
// [EOF]
