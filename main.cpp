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

	engine::ITime* pTime = engine::GetTime();

	engine::IRealTimeClock* pRTC = pTime->GetRealTimeClock();
	engine::ITimer* pGC = pTime->GetGameClock();

	double lastTick = 0.0;
	float frameCount = 0.0f;
	bool run = true;
	while (run)
	{
		pGC->Tick();
		double time = pRTC->GetRealTimePrecise();
		double timePeriod = time-lastTick;
		if (timePeriod >= 1.0)
		{
			printf("Framerate: %.02ffps\n", frameCount/timePeriod);
			printf("GameClock: %f\n", pGC->GetFrameTimePrecise());
			lastTick = time;
			frameCount = 0.0f;
		}
	
		run = display.Update(&screen);
		run &= !engine::CKeyboard::IsKeyPressed(GLFW_KEY_ESC);
	
		++frameCount;

		double timeTaken = pRTC->GetRealTimePrecise()-time;
		double timeToWait = FRAME_INTERVAL - timeTaken;
		pTime->Sleep(timeToWait * 1000000.0);
	}

	printf("All done.\n");

	engine::CKeyboard::Uninitialise();
	return 0;
}
