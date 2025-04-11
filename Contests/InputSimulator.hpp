#ifndef INPUT_SIMULATOR_HPP
#define INPUT_SIMULATOR_HPP

#include <windows.h>
#include <iostream>


//////////////////////////////////////
//	POINT pos;						//
//	GetCursorPos(&pos);				//
//////////////////////////////////////

//////////////////////////////////////
//	#include <conio.h>
//	_kbhit(); // if key is pressed
//	_getch(); // get key pressed
//////////////////////////////////////

inline void LeftClick()
{
	// Simulate a left mouse button down event
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(INPUT));

	// Simulate a left mouse button up event
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(INPUT));
}

inline void LeftClick(int x, int y)
{
	// Set the mouse cursor position
	SetCursorPos(x, y);

	// Simulate a left mouse button down event
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(INPUT));

	// Simulate a left mouse button up event
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(INPUT));
}

inline void RightClick()
{
	// Simulate a left mouse button down event
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &input, sizeof(INPUT));

	// Simulate a left mouse button up event
	input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &input, sizeof(INPUT));
}

inline void RightClick(int x, int y)
{
	// Set the mouse cursor position
	SetCursorPos(x, y);

	// Simulate a left mouse button down event
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &input, sizeof(INPUT));

	// Simulate a left mouse button up event
	input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &input, sizeof(INPUT));
}

inline void KeyPress(WORD virtualKey)
{
	INPUT input[2] = { 0 };

	// Press
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = virtualKey;

	// Release
	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = virtualKey;
	input[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(2, input, sizeof(INPUT)); // Send both events
}

inline void PressCtrlV() {

	INPUT input[4] = { 0 };

	// Press CONTROL
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = VK_CONTROL;

	// Press V
	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = 'V';

	// Release V
	input[2].type = INPUT_KEYBOARD;
	input[2].ki.wVk = 'V';
	input[2].ki.dwFlags = KEYEVENTF_KEYUP;

	// Release CONTROL
	input[3].type = INPUT_KEYBOARD;
	input[3].ki.wVk = VK_CONTROL;
	input[3].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(4, input, sizeof(INPUT)); // Send events
}

#pragma region Utils


//// Keyboard hook procedure
//LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
//	if (nCode == HC_ACTION) { // If it's a keyboard action
//		KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
//
//		if (wParam == WM_KEYDOWN) {
//			std::cout << "Key pressed: " << kbStruct->vkCode << std::endl;
//		}
//		else if (wParam == WM_KEYUP) {
//			std::cout << "Key released: " << kbStruct->vkCode << std::endl;
//		}
//	}
//	return CallNextHookEx(nullptr, nCode, wParam, lParam);
//}
//
//int main()
//{
//	ios_base::sync_with_stdio(0);
//	cout.tie(0);
//	cin.tie(0);
//
//	// Set the keyboard hook
//	HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, nullptr, 0);
//	if (!keyboardHook) {
//		std::cerr << "Failed to install hook!" << std::endl;
//		return 1;
//	}
//
//	// Enter a message loop to keep the hook running
//	MSG msg;
//	while (GetMessage(&msg, nullptr, 0, 0)) {
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	UnhookWindowsHookEx(keyboardHook);
//	return 0;
//
//}

#pragma endregion

#endif // !INPUT_SIMULATOR_HPP
