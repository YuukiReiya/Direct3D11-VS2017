/*!
	@file	MAIN.cpp
	@date	2018/11/10
	@author	�ԏ� �G�P
	@brief	�A�v���P�[�V�������C���G���g���[�|�C���g
*/
#include <tchar.h>
#include "Main.h"
#include "../Direct3D11/Direct3D11.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
//#include "../Sound/SoundManager/SoundManager.h"
//#include "../Shader/ShaderManager.h"
#include "../Camera/Camera.h"


/*!
	@brief	���O���
*/
using namespace std;
using namespace D3D11;

/*!
	@def	�萔
*/
const std::string Main::c_AppName = "App";						/*!< �A�v���P�[�V�����̖��O */
const int	Main::c_FPS = 60;									/*! �Q�[���̃^�[�Q�b�gFPS */
const float Main::c_MinFrameTime = 1.0f / Main::c_FPS;			/*!< 1�t���[���ӂ�̌o�ߎ��� */


/*!
	@brief	�R���X�g���N�^
*/
Main::Main() :m_pWindow(nullptr)
{
}

/*!
	@brief	�f�X�g���N�^
*/
Main::~Main()
{
	Finalize();
}

/*!
	@brief	������
*/
bool Main::Initialize(HINSTANCE hInstance)
{
	/*! �E�B���h�E�̃C���X�^���X�𐶐� */
	m_pWindow = make_unique<Window>();

	auto  tmp = tString(c_AppName);
	const auto appName = const_cast<LPCTSTR>(tmp.c_str());

	/*! �E�B���h�E�쐬 */
	if (!m_pWindow->Init(&m_hWnd, hInstance,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, appName)) {
		return false;
	}

	/*! Direct3D�f�o�C�X�̏����� */
	if (!Direct3D11::GetInstance().Initialize(m_hWnd)) { return false; }

	/*! ���������� */
	return true;
}

/*!
	@brief	�j��
*/
void Main::Finalize()
{
	Release();/*!< �ϐ��̊J�� */
}

/*!
	@brief	���
*/
void Main::Release()
{
	//Direct3D11::GetInstance().ReportCOMs();

	/*! �E�B���h�E�̊J�� */
	m_pWindow.reset();

	/*! Direct3D�f�o�C�X�̊J�� */
	Direct3D11::GetInstance().Release();

	/*! �T�E���h�}�l�[�W���[�̊J�� */
	//SoundManager::GetInstance().Release();

	//������V�F�[�_�[�̊J�����s���Ă��Ȃ����߃��������[�N����

}

/*!	
	@brief	�A�v���P�[�V���������̓����
*/
void Main::Loop()
{
	HRESULT hr;

	/*! �T�E���h�}�l�[�W���[�̏����� */
	//hr = SoundManager::GetInstance().Initialize();
	//if (FAILED(hr)) {
	//	return;
	//}

	/*! �V�F�[�_�[�Ǘ��N���X�̏����� */
	//hr = ShaderManager::GetInstance().Initialize();
	//if (FAILED(hr)) {
	//	return;
	//}

	/*! �J�����̏����� */
	Camera::GetInstance().Initialize({ 0,0,-1 });

	/*! �V�[���̏����� */
	m_pRoot = make_unique<SceneRoot>();
	m_pRoot->Initialize();

	/*! FPS�̏����� */
	SetUpFPS();

	/*! ���b�Z�[�W���[�v */
	MSG msg{ 0 };
	SecureZeroMemory(&msg, sizeof(&msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			App();/*!< App���� */
		}
	}
}

/*
	@brief	���𑜓x�^�C�}�[���Ή����Ă��邩�m�F
*/
bool Main::HighQualityTimmer()
{
	/*! QueryPerformanceFrequency�̑Ή������� */
	if (!QueryPerformanceFrequency(&m_TimeFreq)) {
		ErrorLog("This PC is not fit QueryPerformanceFrequency!\n"
			"Sorry this project is exit!");
		return false;
	}

	return true;
}

/*!
	@brief	�A�v���P�[�V��������
*/
void Main::App()
{
	/*! FPS�m�F */
#ifdef DEBUG_FPS
	static DWORD time = 0;
	static int frame = 0;
	frame++;
	char str[50];
	sprintf_s(str, "fps=%d", frame);
	if (timeGetTime() - time > 1000) {
		time = timeGetTime();
		frame = 0;

		auto tmp = tString(str);
		const auto fps = const_cast<LPTSTR>(tmp.c_str());
		if (!SetWindowText(m_hWnd, fps)) {
			WindowsErrorLog();
		}
	}
#endif
	/*! FPS�̒������@�ŕ��� */
#ifdef Vsync
	/*! �X�V���� */
	Update();
	/*! �`�揈�� */
	Render();
#else
	/*! �X�V���� */
	Update();
	/*! �`�揈�� */
	Render();
	/*! FPS���� */
	SleepApp();
#endif // Vsync
}

/*!
	@brief	�X�V
*/
void Main::Update()
{
	/*! �V�[���̍X�V */
	m_pRoot->Update(m_pRoot.get());
}

/*!
	@brief	�`��
*/
void Main::Render()
{
	/*! �`��^�[�Q�b�g�̃N���A */
	Direct3D11::GetInstance().Clear();

	/*! �V�[���̕`�� */
	m_pRoot->Render();

	/*! ��ʍX�V */
	Direct3D11::GetInstance().Present();
}

/*!
	@brief	FPS�����̏���
*/
void Main::SetUpFPS()
{
	m_FrameTime = 0;
	/*! ����̌v�Z */
	QueryPerformanceCounter(&m_TimeStart);
}
/*!
	@brief	�A�v���P�[�V���������̂��x��
*/
void Main::SleepApp()
{
	/*! ���̎��Ԃ��擾 */
	QueryPerformanceCounter(&m_TimeEnd);
	/*! �o�ߎ��� */
	m_FrameTime = static_cast<float>(m_TimeEnd.QuadPart - m_TimeStart.QuadPart) / static_cast<float>(m_TimeFreq.QuadPart);
	if (m_FrameTime < c_MinFrameTime)
	{
		DWORD SleepTime = static_cast<DWORD>((c_MinFrameTime - m_FrameTime) * 1000);/*!< �Y���� */
		timeBeginPeriod(1);	/*!< ���𐫔\���グ�� */
		Sleep(SleepTime);	/*!< ���x�� */
		timeEndPeriod(1);	/*!< �߂� */
	}
	QueryPerformanceCounter(&m_TimeStart);
}
