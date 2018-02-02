#include "InputController.h"
#include <Windows.h>
#include <conio.h>
bool InputController::CheckKbHit()
{
	bool ret = false;
	if (_kbhit())
	{
		ret = true;
	}
	return ret;
}
char InputController::GetInputChar()
{
	return _getch();
}