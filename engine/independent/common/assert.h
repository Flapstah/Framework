#if !defined(__ASSERT_H__)
#define __ASSERT_H__

//==============================================================================

//#include "common/ilogfile.h"

//==============================================================================

namespace engine
{
	//============================================================================

#if defined(NO_ASSERTS)
#define assert(_condition_)
#define assertf(_condition_, _reason_)
#else
#define assert(_condition_) \
	if (!(_condition_)) \
	{ \
		/*
		if (engine::g_AssertLog->PushBehaviours()) \
		{ \
			engine::g_AssertLog->TurnOffBehaviours(static_cast<engine::ILogFile::eBehaviourFlag>(engine::ILogFile::eBF_OutputHeader | engine::ILogFile::eBF_OutputFooter | engine::ILogFile::eBF_OutputToFile)); \
			LogAssert("%s(%i): ", __FILE__, __LINE__); \
			engine::g_AssertLog->PopBehaviours(); \
			engine::g_AssertLog->PushBehaviours(); \
			engine::g_AssertLog->TurnOffBehaviours(static_cast<engine::ILogFile::eBehaviourFlag>(engine::ILogFile::eBF_LineCount | engine::ILogFile::eBF_OutputToFile)); \
			LogAssert("condition (%s)", #_condition_); \
			engine::g_AssertLog->PopBehaviours(); \
			engine::g_AssertLog->PushBehaviours(); \
			engine::g_AssertLog->TurnOffBehaviours(static_cast<engine::ILogFile::eBehaviourFlag>(engine::ILogFile::eBF_OutputToDebugger)); \
			LogAssert("%s(%i): condition (%s)", __FILE__, __LINE__, #_condition_); \
			engine::g_AssertLog->PopBehaviours(); \
		} \
		else \
		{ \
			LogAssert("%s(%i): ", __FILE__, __LINE__, #_condition_); \
			LogAssert("*ASSERT* condition (%s)", #_condition_); \
		} \
		*/ \
		DEBUG_BREAK; \
	}

#define assertf(_condition_, ...) \
	if (!(_condition_)) \
	{ \
		/*
		if (engine::g_AssertLog->PushBehaviours()) \
		{ \
			engine::g_AssertLog->TurnOffBehaviours(static_cast<engine::ILogFile::eBehaviourFlag>(engine::ILogFile::eBF_OutputHeader | engine::ILogFile::eBF_OutputFooter | engine::ILogFile::eBF_OutputToFile)); \
			LogAssert("%s(%i): ", __FILE__, __LINE__); \
			engine::g_AssertLog->PopBehaviours(); \
			engine::g_AssertLog->PushBehaviours(); \
			engine::g_AssertLog->TurnOffBehaviours(static_cast<engine::ILogFile::eBehaviourFlag>(engine::ILogFile::eBF_LineCount | engine::ILogFile::eBF_OutputFooter | engine::ILogFile::eBF_OutputToFile)); \
			LogAssert("condition (%s) : ", #_condition_); \
			engine::g_AssertLog->PopBehaviours(); \
			engine::g_AssertLog->PushBehaviours(); \
			engine::g_AssertLog->TurnOffBehaviours(static_cast<engine::ILogFile::eBehaviourFlag>(engine::ILogFile::eBF_OutputHeader | engine::ILogFile::eBF_OutputToFile)); \
			LogAssert(__VA_ARGS__); \
			engine::g_AssertLog->PopBehaviours(); \
			engine::g_AssertLog->PushBehaviours(); \
			engine::g_AssertLog->TurnOffBehaviours(static_cast<engine::ILogFile::eBehaviourFlag>(engine::ILogFile::eBF_OutputFooter | engine::ILogFile::eBF_OutputToDebugger)); \
			LogAssert("%s(%i): condition (%s) : ", __FILE__, __LINE__, #_condition_); \
			engine::g_AssertLog->PopBehaviours(); \
			engine::g_AssertLog->PushBehaviours(); \
			engine::g_AssertLog->TurnOffBehaviours(static_cast<engine::ILogFile::eBehaviourFlag>(engine::ILogFile::eBF_OutputHeader | engine::ILogFile::eBF_OutputToDebugger)); \
			engine::g_AssertLog->TurnOnBehaviours(static_cast<engine::ILogFile::eBehaviourFlag>(engine::ILogFile::eBF_FlushEachWrite)); \
			LogAssert(__VA_ARGS__); \
			engine::g_AssertLog->PopBehaviours(); \
		} \
		else \
		{ \
			LogAssert("%s(%i): ", __FILE__, __LINE__, #_condition_); \
			LogAssert("condition (%s) : ", #_condition_); \
			LogAssert(__VA_ARGS__); \
		} \
		*/ \
		DEBUG_BREAK; \
	}
#endif

	//============================================================================
} // End [namespace engine]

//==============================================================================

#endif // End [!defined(__ASSERT_H__)]
// [EOF]
