// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

HANDLE handle;

void setup()
{
	wprintf(L"Press x to exit");
	handle = GetStdHandle(STD_INPUT_HANDLE);
}

// the loop routine runs over and over again forever:
void loop()
{
	KEY_EVENT_RECORD *currentEvent = NULL;
	DWORD             eventCount;
	INPUT_RECORD      inputRecord;
	PeekConsoleInput(handle, &inputRecord, 1, &eventCount);
	if (eventCount > 0)
	{
		// Read it.
		ReadConsoleInput(handle, &inputRecord, 1, &eventCount);
		currentEvent = &(inputRecord.Event.KeyEvent);
		//// Filter for key events and only display it for the key being down.
		//// Option for filtering the holding of a key are limited so omitted here.
		if (inputRecord.EventType == KEY_EVENT && currentEvent->bKeyDown)
		{
			wprintf(L"Detected key-press: %d. (%c)\n", currentEvent->wVirtualKeyCode, currentEvent->uChar.AsciiChar);
		}
	}
}