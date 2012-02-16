#include "common/stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/glfw.h>

#include "common/itime.h"

#include "graphics/display.h"
#include "input/keyboard.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (400)

#define DESIRED_FRAMERATE (10.0)
#define FRAME_INTERVAL (1.0/DESIRED_FRAMERATE)

void DumpArgs(int argc, char* argv[])
{
	printf("*** Passed %d arguments:\n", argc);
	for (int i = 0; i < argc; ++i)
	{
		printf("[%d] [%s]\n", i, argv[i]);
	}
	printf("*** End argument list\n");
}

void DumpVariableSizes(void)
{
	printf("*** Variable sizes\n");
#define PRINT_SIZE(_type_) printf(#_type_ "\t: %u\n", static_cast<uint32>(sizeof(_type_)))
	PRINT_SIZE(int8);
	PRINT_SIZE(int16);
	PRINT_SIZE(int32);
	PRINT_SIZE(int64);
	PRINT_SIZE(uint8);
	PRINT_SIZE(uint16);
	PRINT_SIZE(uint32);
	PRINT_SIZE(uint64);
	PRINT_SIZE(bool);
	PRINT_SIZE(float);
	PRINT_SIZE(double);
#undef PRINT_SIZE
	printf("*** End variable sizes\n");
}

int main(int argc, char* argv[])
{
//	IGNORE_PARAMETER(argc);
//	IGNORE_PARAMETER(argv);
	DumpArgs(argc, argv);

	uint32 screen[WINDOW_WIDTH*WINDOW_HEIGHT];
	for (uint32 i = 0; i < WINDOW_WIDTH*WINDOW_HEIGHT; ++i)
	{
		screen[i] = 0x00ff0000;
	}

	engine::CDisplay display(WINDOW_WIDTH, WINDOW_HEIGHT, "Framework test");
	engine::CKeyboard::Initialise();

	engine::ITime* pTime = engine::GetTime();

	engine::IRealTimeClock* pRTC = pTime->GetRealTimeClock();
	engine::ITimer* pGC = pTime->GetGameClock();

	double time = 0.0;
	double timeCount = 0.0;
	double frameCount = 0.0;

	bool run = true;
	while (run)
	{
		timeCount += pRTC->Tick();
		time += pGC->Tick();

		if (time >= FRAME_INTERVAL)
		{
			time -= FRAME_INTERVAL;
			++frameCount;
			run = display.Update(&screen);
		}

		run &= !engine::CKeyboard::IsKeyPressed(GLFW_KEY_ESC);

		if (timeCount >= 1.0)
		{
			printf("*** Framerate: frames %.02f time %.02f %.02ffps\n", frameCount, timeCount, frameCount/timeCount);
			timeCount -= 1.0;
			frameCount = 0.0;
		}
	}

	printf("********\n");
//	DumpVariableSizes();
	printf("All done.\n");

	engine::CKeyboard::Uninitialise();
	return 0;
}
