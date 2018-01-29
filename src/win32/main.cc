#include <Windows.h>
#include <stdint.h>
#include "../vinput.h"

using namespace std;
 

inline void  mapAbsPoint(int32_t & x, int32_t & y) {
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	x = 65536 * x / width + (x < 0 ? -1 : 1);
	y = 65536 * y / height + (y < 0 ? -1 : 1);
}

void mouseMove(int x, int y) {
	mapAbsPoint(x, y);
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dx = x;
	input.mi.dy = y;
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	input.mi.time = 0;
	input.mi.dwExtraInfo = 0;
	input.mi.mouseData = 0;
	SendInput(1, &input, sizeof(input));
}

void mousePress(int x, int y, int button, bool down) {
	if (button < 0 || button > 2)
		return;
	static const DWORD Map[2][3] = {
		{ MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_RIGHTDOWN },
		{ MOUSEEVENTF_LEFTUP, MOUSEEVENTF_MIDDLEUP, MOUSEEVENTF_RIGHTUP }
	};
	mapAbsPoint(x, y);
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dx = x;
	input.mi.dy = y;
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | Map[down ? 0 : 1][button];
	input.mi.time = 0;
	input.mi.dwExtraInfo = 0;
	input.mi.mouseData = 0;
	SendInput(1, &input, sizeof(input));
}


void keyPress(int keyCode, bool down) {
	INPUT input = {0};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = keyCode;
	input.ki.dwFlags = down ? 0 : KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(input));
}
 