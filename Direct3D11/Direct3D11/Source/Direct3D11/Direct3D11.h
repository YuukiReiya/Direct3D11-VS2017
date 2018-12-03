/*
	@file	Direct3D11.h
	@date	2018/11/10
	@author	番場 宥輝
	@brief	Direct3D11デバイス
	@detail	シングルトン
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
	@brief	Vsyncを使ったFPS同期(コメントアウトするとアプリケーション側でのwait)
*/
//#define Vsync

/*!
	@def	定数宣言
*/
const INT WINDOW_WIDTH	= 1920;
const INT WINDOW_HEIGHT = 1080;

/*! Direct3D11関連の名前空間 */
namespace D3D11 {

	/*!
		@brief	Direct3D11デバイスclass
	*/
	class Direct3D11
		:public Singleton<Direct3D11>
	{
	public:
		~Direct3D11();

		/*! 関数 */
		bool Initialize(HWND hWnd);
		void Release();
		void Clear();
		void Present();
		void ReportCOMs(std::string firstMessage = "");

		/*! ゲッター */
		ID3D11Device* GetDevice()const { return m_pDevice.Get(); }
		ID3D11DeviceContext* GetDeviceContext()const { return m_pDeviceContext.Get(); }
	private:
		friend class Singleton<Direct3D11>;
		Direct3D11();

		/*! 定数 */
		static const float c_ClearColor[4];

	public:
		/*! 変数 */
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

