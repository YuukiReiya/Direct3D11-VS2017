/*
	@file	Texture.h
	@date	2018/11/22
	@author	�ԏ� �G�P
	@brief	�e�N�X�`��
*/
#pragma once
#include <D3D11.h>
#include <string>
#include <DirectXMath.h>
#include <wrl/client.h>
#include "../ITexture/ITexture.h"

/*! API�̖��O��ԂɊ܂߂� */
namespace API {

	class Texture
		: public ITexture
	{
	public:
		/*!
			@brief	�R���X�g���N�^
		*/
		explicit Texture();

		/*!
			@brief	�f�X�g���N�^
		*/
		~Texture()override;

		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂ƃT���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@return		����:S_OK ���s:E_FAIL

		*/
		HRESULT Initialize(std::string filePath);

		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂Ɖ摜�T�C�Y�̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@param[in]	�摜�T�C�Y
			@return		����:S_OK ���s:E_FAIL
		*/
		HRESULT Initialize(std::string filePath, const DirectX::XMINT2 size);

		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂ƃT���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@param[in]	�^�C�����O���[�h�̐ݒ�
			@return		����:S_OK ���s:E_FAIL
		*/
		HRESULT Initialize(std::string filePath, const TileMode tileMode);

		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂Ɖ摜�T�C�Y�̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@param[in]	�摜�T�C�Y
			@param[in]	�^�C�����O���[�h�̐ݒ�
			@return		����:S_OK ���s:E_FAIL
		*/
		HRESULT Initialize(std::string filePath, const DirectX::XMINT2 size, const TileMode tileMode);
	
		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂Ɖ摜�T�C�Y�̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@param[in]	�t�B���^�����O���[�h�̐ݒ�
			@return		����:S_OK ���s:E_FAIL
		*/
		HRESULT Initialize(std::string filePath, const FilteringMode filterMode);
		
		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂Ɖ摜�T�C�Y�̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@param[in]	�摜�T�C�Y
			@param[in]	�t�B���^�����O���[�h�̐ݒ�
			@return		����:S_OK ���s:E_FAIL
		*/
		HRESULT Initialize(std::string filePath, const DirectX::XMINT2 size, const FilteringMode filterMode);

		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂Ɖ摜�T�C�Y�̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@param[in]	�^�C�����O���[�h�̐ݒ�
			@param[in]	�t�B���^�����O���[�h�̐ݒ�
			@return		����:S_OK ���s:E_FAIL
		*/
		HRESULT Initialize(std::string filePath, const TileMode tileMode, const FilteringMode filterMode);

		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂Ɖ摜�T�C�Y�̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@param[in]	�摜�T�C�Y
			@param[in]	�^�C�����O���[�h�̐ݒ�
			@param[in]	�t�B���^�����O���[�h�̐ݒ�
			@return		����:S_OK ���s:E_FAIL
		*/
		HRESULT Initialize(std::string filePath, const DirectX::XMINT2 size, const TileMode tileMode, const FilteringMode filterMode);
	
		/*!
			@fn		�t�@�C�i���C�Y
			@brief	�j������
			@detail	�����o�̖����I�ȊJ��
		*/
		void Finalize()override;
	};
};
