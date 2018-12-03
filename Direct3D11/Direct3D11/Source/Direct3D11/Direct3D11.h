/*
	@file	Direct3D11.h
	@date	2018/11/10
	@author	�ԏ� �G�P
	@brief	Direct3D11�f�o�C�X
	@detail	�V���O���g��
*/
#pragma once
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"winmm.lib")

#include <D3D11.h>
#include <string>
#include <wrl/client.h>
#include "../Singleton/Singleton.h"

/*!
	@def	Vsync
	@brief	Vsync���g����FPS����(�R�����g�A�E�g����ƃA�v���P�[�V�������ł�wait)
*/
//#define Vsync

/*!
	@def	�萔�錾
*/
const INT WINDOW_WIDTH	= 1920;
const INT WINDOW_HEIGHT = 1080;

/*! Direct3D11�֘A�̖��O��� */
namespace D3D11 {

	/*!
		@brief	Direct3D11�f�o�C�Xclass
	*/
	class Direct3D11
		:public Singleton<Direct3D11>
	{
	public:
		~Direct3D11();

		/*! �֐� */
		bool Initialize(HWND hWnd);
		void Release();
		void Clear();
		void Present();
		void ReportCOMs(std::string firstMessage = "");

		/*! �Q�b�^�[ */
		ID3D11Device* GetDevice()const { return m_pDevice.Get(); }
		ID3D11DeviceContext* GetDeviceContext()const { return m_pDeviceContext.Get(); }
	private:
		friend class Singleton<Direct3D11>;
		Direct3D11();

		/*! �萔 */
		static const float c_ClearColor[4];

	public:
		/*! �ϐ� */
		Microsoft::WRL::ComPtr<ID3D11Device>			m_pDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>		m_pDeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain>			m_pSwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_pRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_pDepthStencilView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pDepthStencil;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	m_pDepthStencilState;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState>	m_pRasterizerState;
		Microsoft::WRL::ComPtr<ID3D11Debug>				m_pDebug;
	};
};

