#include <common/stdafx.h>

#include <stdio.h>
#include <stdlib.h>

#include <GL/glfw.h>

#include "common/types.h"
#include "common/macros.h"
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

int main(int argc, char* argv[])
{
	DumpArgs(argc, argv);

//	IGNORE_PARAMETER(argc);
//	IGNORE_PARAMETER(argv);

	uint32 screen[WINDOW_WIDTH*WINDOW_HEIGHT];
	for (uint32 i = 0; i < WINDOW_WIDTH*WINDOW_HEIGHT; ++i)
	{
		screen[i] = 0x00ff0000;
	}

	engine::CDisplay display(WINDOW_WIDTH, WINDOW_HEIGHT, "Framework test");
	engine::CKeyboard::Initialise();

	engine::IRealTimeClock* pRTC = engine::GetRealTimeClock();
	engine::ITimer* pGC = engine::GetGameClock();

	bool run = true;
	while (run)
	{
		pGC->Tick();
		double time = pRTC->GetRealTimePrecise();

		run = display.Update(&screen);
		run &= !engine::CKeyboard::IsKeyPressed(GLFW_KEY_ESC);

		double timeTaken = pRTC->GetRealTimePrecise() - time;
		double timeToWait = FRAME_INTERVAL - timeTaken;

		SLEEP(timeToWait * 1000.0);
	}

	printf("All done.\n");

	engine::CKeyboard::Uninitialise();
	return argc;
}
