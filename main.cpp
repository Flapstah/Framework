#include <stdio.h>
#include <stdlib.h>

#include "common/types.h"
#include "common/macros.h"
#include "graphics/display.h"
#include "input/keyboard.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (400)

void DumpArgs(int argc, char* argv[])
{
	printf("Passed arguments:\n");
	for (int i = 0; i < argc; ++i)
	{
		printf("arg %d: [%s]\n", i, argv[i]);
	}
}

int main(int argc, char* argv[])
{
	printf("main\n");
	IGNORE_PARAMETER(argc);
	IGNORE_PARAMETER(argv);

	printf("clear screen\n");
	uint32 screen[WINDOW_WIDTH*WINDOW_HEIGHT];
	for (uint32 i = 0; i < WINDOW_WIDTH*WINDOW_HEIGHT; ++i)
	{
		screen[i] = 0x00ff0000;
	}

	printf("init keyboard\n");
	CKeyboard::Initialise();
	printf("init display\n");
	CDisplay display(WINDOW_WIDTH, WINDOW_HEIGHT, "Framework test");

	bool run = true;
	printf("update display\n");
	while (run)
	{
		run = display.Update(&screen);
	}

	printf("All done.\n");

	CKeyboard::Uninitialise();
	return argc;
}
