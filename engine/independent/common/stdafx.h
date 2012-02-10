// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include "targetver.h"
#endif // defined(_WIN32) || defined(_WIN64)

#if defined(__linux__)
#include <unistd.h>
#endif // defined(__linux__)

#include <stdio.h>

// TODO: reference additional headers your program requires here
//#include <assert.h>
#include <time.h>

#include "common/platform_stdafx.h"

#include "common/types.h"
#include "common/assert.h"
#include "common/macros.h"
