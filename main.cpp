#include <stdio.h>
#include <stdlib.h>

#include <GL/glfw.h>

#include "common/types.h"
#include "common/macros.h"
#include "graphics/display.h"
#include "input/keyboard.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (400)

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

	CDisplay display(WINDOW_WIDTH, WINDOW_HEIGHT, "Framework test");
	CKeyboard::Initialise();

	bool run = true;
	while (run)
	{
		run = display.Update(&screen);
		run &= !CKeyboard::IsKeyPressed(GLFW_KEY_ESC);
	}

	printf("All done.\n");

	CKeyboard::Uninitialise();
	return argc;
}
