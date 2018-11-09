/*!
	@file	Window.h
	@date	2018/02/22
	@author	�ԏ� �G�P
	@brief	WindowsAPI�̃E�B���h�E����
*/
#pragma once
#include <Windows.h>

class Window
{
public:
	Window() = default;
	~Window();

	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool Init(HWND* hWnd,HINSTANCE hInstance,INT iX,INT iY,INT iWidth,INT iHeight, LPCTSTR WindowName);
};

