#include "KeyboardController.h"


KeyboardController::KeyboardController()
{
}


KeyboardController::~KeyboardController()
{
}

void KeyboardController::init()
{
	handle = GetStdHandle(STD_INPUT_HANDLE);
}

void KeyboardController::processEvents() {
	KEY_EVENT_RECORD *currentEvent = NULL;
	DWORD             eventCount;
	INPUT_RECORD      inputRecord;

	PeekConsoleInput(handle, &inputRecord, 1, &eventCount);
	// See if there was an event
	if (eventCount > 0)
	{
		// Read it.
		ReadConsoleInput(handle, &inputRecord, 1, &eventCount);
		currentEvent = &(inputRecord.Event.KeyEvent);
		// Filter for key events and only display it for the key being down.
		// Option for filtering the holding of a key are limited so omitted here.
		if (inputRecord.EventType == KEY_EVENT && currentEvent->bKeyDown)
		{
			switch (currentEvent->wVirtualKeyCode)
			{
				case 27:	// Esc
					exitFlag = true;
					break;
				case 87:	// W
					moveForwardFlag = true;
					break;
				case 83:	// S
					moveBackwardFlag = true;
					break;
				case 88:	// X
					stopFlag = true;
					break;
			}
		}
	}
}

bool KeyboardController::shouldExit()
{
	bool result = exitFlag;
	clearFlags();
	return result;
}

bool KeyboardController::shouldMoveForward()
{
	bool result = moveForwardFlag;
	clearFlags();
	return result;
}


bool KeyboardController::shouldMoveBack()
{
	bool result = moveBackwardFlag;
	clearFlags();
	return result;
}


bool KeyboardController::shouldStop()
{
	bool result = stopFlag;
	clearFlags();
	return result;
}

void KeyboardController::clearFlags()
{
	stopFlag = moveBackwardFlag = moveForwardFlag = exitFlag = false;
}