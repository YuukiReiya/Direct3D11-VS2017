/*!
	@file	Main.h
	@date	2018/11/10
	@author	番場 宥輝
	@brief	アプリケーションメインエントリーポイント
*/

#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <memory>
#include "../Window/Window.h"
#include "../Scene/Root/SceneRoot.h"

class Main
{
public:
	Main();
	~Main();

	bool Initialize(HINSTANCE hInstance);
	void Finalize();
	void Release();
	void Loop();
	bool HighQualityTimmer();
	void SetUpFPS();
private:
	void App();
	void Update();
	void Render();
	void SleepApp();

	static const std::string c_AppName;
	static const int	c_FPS;
	static const float	c_MinFrameTime;

	HWND	m_hWnd;
	float	m_FrameTime;
	float	m_Fps;
	LARGE_INTEGER m_TimeStart;
	LARGE_INTEGER m_TimeEnd;
	LARGE_INTEGER m_TimeFreq;

	std::unique_ptr<Window>		m_pWindow;	/*< ウィンドウ */
	std::unique_ptr<SceneRoot>	m_pRoot;	/*< シーン変数 */
};

