/*
	@file	ITexture.h
	@date	2018/11/20
	@author	�ԏ� �G�P
	@brief	�e�N�X�`���̃C���^�[�t�F�C�X�Ƃ��Đ��삵�����ۃN���X
	@detail	�ʏ�e�N�X�`���ƃA�g���X�e�N�X�`����ʃN���X�ō�邽�ߋ��ʂȏ��������������N���X�Ƃ��č쐬
*/
#pragma once
#include <D3D11.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include <string>

/*!
	@namespace	API
	@brief		API���O��ԂɊ܂߂�
*/
namespace API {

	class ITexture abstract
	{
	public:
		/*!
			@enum	TileMode
			@brief	�^�C�����O���[�h�̐ݒ�
		*/
		enum TileMode
		{
			/*! �J��Ԃ����� */
			Clamp = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP,			/*!< �f�t�H���g */
			Border = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER,			/*!< SAMPLER_DESC�܂���HLSL�Ŏw�肵�����E�F��ݒ� */
			MirrorOnce = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR_ONCE,
			/*! �^�C�����O */
			Wrap = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP,			/*!< �J��Ԃ� */
			Mirror = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR,			/*!< �J��Ԃ����] */

		};

		/*!
			@enum	FilteringMode
			@brief	�t�B���^�����O���[�h�̐ݒ�
		*/
		enum FilteringMode
		{
			Point = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT,			/*!< �|�C���g�t�B���^�����O:�ň��i���ŃR�X�p�� */
			Bilinear = D3D11_FILTER::D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,	/*!< �o�C���j�A�e�N�X�`���t�B���^�����O */
			Trilinear = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR,		/*!< �g�����j�A�e�N�X�`���t�B���^�����O:�f�t�H���g�ݒ� */
			Anisotropic = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC			/*!< �ٕ����t�B���^�����O:�ō��i���ŃR�X�p�� */
		};

		/*!
			@brief	�R���X�g���N�^
		*/
		ITexture();

		/*!
			@brief	���z�f�X�g���N�^
		*/
		virtual ~ITexture();

		/*!
			@fn		�t�@�C�i���C�Y
			@brief	�j������
			@detail	�����o�̖����I�ȊJ��
					�h����Ń����o�������邱�Ƃ𓥂܂��A���z�֐��Ƃ��Ď���
		*/
		virtual void Finalize();

		/*!
			@fn			�摜�T�C�Y�̃Z�b�^�[
			@brief		�ǂݍ��މ摜�̃T�C�Y�̐ݒ�
			@param[in]	�摜�T�C�Y
			@return		����:true ���s:false
		*/
		bool SetSize(const DirectX::XMINT2 size);

		/*!
			@fn			�摜�T�C�Y�̃Q�b�^�[
			@brief		�摜�T�C�Y�̎擾
			@detail		SetSize�Ŏw�肵���摜�̃T�C�Y���擾
		*/
		inline DirectX::XMINT2 GetSize()const { return m_Size; }

		inline ID3D11SamplerState**GetSamplerState() { return m_pSamplerState.GetAddressOf(); }
		inline ID3D11ShaderResourceView**GetShaderResourceView() { return m_pShaderResourceView.GetAddressOf(); }
		/*!
			@fn			�^�C�����O���[�h�ƃt�B���^�����O���[�h�̃Z�b�^�[
			@brief		�^�C�����O���[�h�ƃt�B���^�����O���[�h�̐ݒ�
			@param[in]	�ݒ肷��^�C�����[�h
			@param[in]	�ݒ肷��t�B���^�����O(�A�h���b�V���O���[�h)
			@detail		�T���v���[�X�e�[�g���쐬
		*/
		HRESULT SetTileAndFiltering(const TileMode tileMode, const FilteringMode filterMode);
	protected:
		TileMode		m_eTileMode;	/*!< �^�C�����O���[�h */
		FilteringMode	m_eFilterMode;	/*!< �t�B���^�����O���[�h */
		DirectX::XMINT2 m_Size;			/*!< �摜�T�C�Y */
		Microsoft::WRL::ComPtr<ID3D11SamplerState>		m_pSamplerState;		/*!< �T���v���[�X�e�[�g */
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>m_pShaderResourceView;	/*!< �V�F�[�_�[���\�[�X�r���[(SRV) */

		/*!
			@fn			�摜�̓ǂݍ���
			@brief		�摜�̓ǂݍ��݂��s��SRV���쐬
			@detail		WIC���g���摜�f�[�^��ǂݍ��݁ASRV���쐬�A�����o�ϐ��Ƀo�C���h
			@param[in]	�ǂݍ��ރt�@�C���̃p�X
			@return		�ǂݎ�茋�� ����:S_OK  ���s:E_FAIL
		*/
		HRESULT Load(std::string filePath);

		/*!
			@var	c_DefaultSize
			@brief	�f�t�H���g�̉摜�T�C�Y
			@detail	�f�t�H���g�ŗ^�����Ă���摜�T�C�Y
		*/
		static const DirectX::XMINT2 c_DefaultSize;
	};
}