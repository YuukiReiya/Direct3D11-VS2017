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
	@def	MSAA
	@brief	�}���`�T���v���E�A���`�G�C���A�X(�R�����g�A�E�g�����MSAA����)
*/
//#define MSAA


/*!
	@var	c_WindowWidth
	@brief	�E�B���h�E�̉���
*/
constexpr INT c_WindowWidth		= 1920;

/*!
	@var	c_WindowHeight
	@brief	�E�B���h�E�̏c��
*/
constexpr INT c_WindowHeight	= 1080;

/*! Direct3D11�֘A�̖��O��� */
namespace D3D11 {

	/*!
		@brief	Direct3D11�f�o�C�Xclass
	*/
	class Direct3D11
		:public Singleton<Direct3D11>
	{
	public:
		/*!
			@brief	�f�X�g���N�^
		*/
		~Direct3D11();

		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�f�o�C�X�̍쐬
			@param[in]	�E�B���h�E�n���h��
			@return		S_OK:���� E_FAIL:���s
		*/
		HRESULT Initialize(HWND hWnd);

		/*!
			@fn		�����[�X
			@brief	�J������
			@detail	�����o�̖����I�ȊJ��
		*/
		void Release();

		/*!
			@fn		�N���A
			@brief	�`��̃N���A
			@detail	�����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V���r���[�̃N���A���s��
		*/
		void Clear();

		/*!
			@fn		��ʍX�V
			@brief	�`��̍X�V
			@detail	�o�b�N�o�b�t�@���t�����g�o�b�t�@�ɐ؂�ւ���
		*/
		void Present();

		/*!
			@fn		COM���|�[�g�̏o��
			@brief	���݂�COM�̐����󋵂��o�̓E�B���h�E�ɏo�͂���
			@detail	�f�o�b�O��p
			@param[in]	�o�̓E�B���h�E�ɏo�͂��郁�b�Z�[�W(���̃��b�Z�[�W���o�͌��COM�̐����󋵂��o��)
		*/
		void ReportCOMs(std::string firstMessage = "");

		/*!
			@fn		�f�o�C�X�̃Q�b�^�[
			@brief	���������f�o�C�X���擾
		*/
		ID3D11Device* GetDevice()const { return m_pDevice.Get(); }

		/*!
			@fn		�R���e�L�X�g�̃Q�b�^�[
			@brief	���������R���e�L�X�g���擾
		*/
		ID3D11DeviceContext* GetDeviceContext()const { return m_pDeviceContext.Get(); }
	private:
		/*!
			@brief	�V���O���g���f�U�C���p�^�[���̃e���v���[�g�p��
		*/
		friend class Singleton<Direct3D11>;

		/*!
			@brief	�R���X�g���N�^
		*/
		Direct3D11();

		/*!
			@var	c_ClearColor
			@brief	�`��^�[�Q�b�g�̃N���A�J���[
		*/
		static const float c_ClearColor[4];

	public:
		Microsoft::WRL::ComPtr<ID3D11Device>			m_pDevice;				/*!< �f�o�C�X */
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>		m_pDeviceContext;		/*!< �R���e�L�X�g */
		Microsoft::WRL::ComPtr<IDXGISwapChain>			m_pSwapChain;			/*!< �X���b�v�`�F�C�� */
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_pRenderTargetView;	/*!< �����_�[�^�[�Q�b�g�r���[ */
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_pDepthStencilView;	/*!< �f�v�X�X�e���V���r���[ */
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pDepthStencil;		/*!< �f�v�X�X�e���V�� */
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	m_pDepthStencilState;	/*!< �f�v�X�X�e���V���X�e�[�g */
		Microsoft::WRL::ComPtr<ID3D11RasterizerState>	m_pRasterizerState;		/*!< ���X�^���C�U�X�e�[�g */
		Microsoft::WRL::ComPtr<ID3D11Debug>				m_pDebug;				/*!< �f�o�b�O */
	};
};

