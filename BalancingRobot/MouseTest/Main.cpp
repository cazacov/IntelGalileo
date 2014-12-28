// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include <exception>
#include <stdio.h>

HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(wchar_t*);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

DWORD cNumRead, fdwMode, i;
INPUT_RECORD irInBuf[128];
int counter = 0;

void setup()
{


	// Get the standard input handle. 

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit(L"GetStdHandle");

	// Save the current input mode, to be restored on exit. 

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit(L"GetConsoleMode");

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit(L"SetConsoleMode");
}

// the loop routine runs over and over again forever:
void loop()
{
	// Wait for the events. 

	if (!ReadConsoleInput(
		hStdin,      // input buffer handle 
		irInBuf,     // buffer to read into 
		128,         // size of read buffer 
		&cNumRead)) // number of records read 
		ErrorExit(L"ReadConsoleInput");

	// Dispatch the events to the appropriate handler. 

	for (i = 0; i < cNumRead; i++)
	{
		switch (irInBuf[i].EventType)
		{
		case KEY_EVENT: // keyboard input 
			KeyEventProc(irInBuf[i].Event.KeyEvent);
			break;

		case MOUSE_EVENT: // mouse input 
			MouseEventProc(irInBuf[i].Event.MouseEvent);
			break;

		case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
			ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
			break;

		case FOCUS_EVENT:  // disregard focus events 

		case MENU_EVENT:   // disregard menu events 
			break;

		default:
			ErrorExit(L"Unknown event type");
			break;
		}
	}
}

VOID ErrorExit(wchar_t* lpszMessage)
{
	wprintf(L"%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
	wprintf(L"Key event: ");

	if (ker.bKeyDown)
		wprintf(L"key pressed\n");
	else wprintf(L"key released\n");
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	wprintf(L"Mouse event: ");

	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			wprintf(L"left button press \n");
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			wprintf(L"right button press \n");
		}
		else
		{
			wprintf(L"button press\n");
		}
		break;
	case DOUBLE_CLICK:
		wprintf(L"double click\n");
		break;
	case MOUSE_HWHEELED:
		wprintf(L"horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		wprintf(L"mouse moved\n");
		break;
	case MOUSE_WHEELED:
		wprintf(L"vertical mouse wheel\n");
		break;
	default:
		wprintf(L"unknown\n");
		break;
	}
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	wprintf(L"Resize event\n");
	wprintf(L"Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}
