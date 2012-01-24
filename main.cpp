#include <stdio.h>
#include <stdlib.h>

#include "common/types.h"
#include "common/macros.h"
#include "graphics/display.h"
#include "input/keyboard.h"

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
	IGNORE_PARAMETER(argc);
	IGNORE_PARAMETER(argv);

	uint32 screen[640*400];
	for (uint32 i = 0; i < 640*480; ++i)
	{
		screen[i] = 0x00ff0000;
	}

	CKeyboard::Initialise();
	CDisplay display(640, 400, "Framework test");

	bool run = true;
	while (run)
	{
		run = display.Update(&screen);
	}

	printf("All done.\n");

	CKeyboard::Uninitialise();
	return argc;
}
