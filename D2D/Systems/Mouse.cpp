#include "stdafx.h"
#include "Mouse.h"

CMouse::CMouse(HWND handle)
	: handle(handle), position(0, 0)
	, wheelValue(0), wheelPrevValue(0), wheelMoveValue(0)
{
	ZeroMemory(buttonStatus, sizeof(BYTE) * 8);
	ZeroMemory(buttonPrevStatus, sizeof(BYTE) * 8);
	ZeroMemory(buttonMap, sizeof(Button) * 8);
	ZeroMemory(buttonCount, sizeof(int) * 8);

	doubleClickTime = GetDoubleClickTime();
}

CMouse::~CMouse()
{
}

void CMouse::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_MOUSEMOVE) {
		position.x = (float)LOWORD(lParam);
		position.y = (float)HIWORD(lParam);
	}

	if (msg == WM_MOUSEWHEEL) {
		short temp = (short)HIWORD(wParam);

		wheelPrevValue = wheelValue;
		wheelValue += (float)temp;
	}
}

void CMouse::Update()
{
	memcpy(buttonPrevStatus, buttonStatus, sizeof(BYTE) * 8);

	ZeroMemory(buttonStatus, sizeof(BYTE) * 8);
	ZeroMemory(buttonMap, sizeof(Button) * 8);

	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;

	for (UINT i = 0; i < 8; i++) {
		BYTE prevStatus = buttonPrevStatus[i];
		BYTE currentStatus = buttonStatus[i];

		if (prevStatus == 0 && currentStatus == 1)
			buttonMap[i] = Button::Down;
		else if (prevStatus == 1 && currentStatus == 0)
			buttonMap[i] = Button::Up;
		else if (prevStatus == 1 && currentStatus == 1)
			buttonMap[i] = Button::Press;
		else
			buttonMap[i] = Button::None;
	}

	// DoubleClick : begin
	// GetTickCount() : 운영체제에서 지금까지 경과한 시간을 얻어옴 int라서 사용안함
	UINT currentTime = GetTickCount();
	for (UINT i = 0; i < 8; i++) {
		if (buttonMap[i] == Button::Down) {
			// 더블 클릭 실패 (시간 내 못 누름)
			if (buttonCount[i] == 1) {
				if (currentTime - startDoubleClickTime[i] >= doubleClickTime)
					buttonCount[i] = 0;
			}

			buttonCount[i]++;
			// 더블클릭 누르기 시작
			if (buttonCount[i] == 1) {
				startDoubleClickTime[i] = currentTime;
			}
		}

		if (buttonMap[i] == Button::Up) {
			// 더블클릭 실패 (시간 내 못 누름)
			if (buttonCount[i] == 1) {
				if (currentTime - startDoubleClickTime[i] >= doubleClickTime) {
					buttonCount[i] = 0;
				}
			}
			// 더블 클릭 성공 
			else if (buttonCount[i] == 2) {
				if (currentTime - startDoubleClickTime[i] < doubleClickTime) {
					buttonMap[i] = Button::DoubleClick;
				}
				buttonCount[i] = 0;
			}
		}
	}
	// DoubleClick : end

	POINT point;
	GetCursorPos(&point);

	ScreenToClient(handle, &point);

	wheelPrevValue = wheelValue;
	wheelMoveValue = wheelValue - wheelPrevValue;
}
