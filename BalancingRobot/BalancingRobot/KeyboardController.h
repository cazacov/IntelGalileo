#pragma once

#include <Windows.h>

class KeyboardController
{
private:
	bool exitFlag;
	bool moveForwardFlag;
	bool moveBackwardFlag;
	bool stopFlag;
	HANDLE handle;

	void clearFlags();
public:
	KeyboardController();
	~KeyboardController();
	void init();
	void processEvents();
	bool shouldExit();
	bool shouldMoveForward();
	bool shouldMoveBack();
	bool shouldStop();
};

