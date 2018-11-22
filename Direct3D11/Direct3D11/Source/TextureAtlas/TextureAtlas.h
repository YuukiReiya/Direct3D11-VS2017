/*
	@file	TextureAtlas.h
	@date	2018/11/20
	@author	�ԏ� �G�P
	@brief	�A�g���X�e�N�X�`��
*/
#pragma once
#include <string>
#include "../ITexture/ITexture.h"

/*!
	@namespace	API
	@brief		API�֘A�̖��O��ԂɊ܂߂�
*/
namespace API {

	class TextureAtlas :
		public ITexture
	{
	public:
		/*!
			@brief	�R���X�g���N�^
		*/
		explicit TextureAtlas();

		/*!
			@brief	�f�X�g���N�^
		*/
		~TextureAtlas()override;

		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂ƕ������̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@param[in]	������(x,y)
			@return		����:S_OK ���s:E_FAIL
		*/
		HRESULT Initialize(std::string filePath, const DirectX::XMINT2 divNum);

		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂ƕ������̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@param[in]	������(x,y)
			@param[in]	�^�C�����O���[�h�̐ݒ�
			@return		����:S_OK ���s:E_FAIL
		*/
		HRESULT Initialize(std::string filePath, const DirectX::XMINT2 divNum, const TileMode tileMode);

		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂ƕ������̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@param[in]	������(x,y)
			@param[in]	�t�B���^�����O���[�h�̐ݒ�
			@return		����:S_OK ���s:E_FAIL
		*/
		HRESULT Initialize(std::string filePath, const DirectX::XMINT2 divNum,const FilteringMode filterMode);

		/*!
			@fn			�C�j�V�����C�Y
			@brief		������
			@detail		�摜�̓ǂݍ��݂ƕ������̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
			@param[in]	�摜�̃p�X
			@param[in]	������(x,y)
			@param[in]	�^�C�����O���[�h�̐ݒ�
			@param[in]	�t�B���^�����O���[�h�̐ݒ�
			@return		����:S_OK ���s:E_FAIL
		*/
		HRESULT Initialize(std::string filePath, const DirectX::XMINT2 divNum, const TileMode tileMode, const FilteringMode filterMode);

		/*!
			@fn		�t�@�C�i���C�Y
			@brief	�j������
			@detail	�����o�̖����I�ȊJ��
		*/
		void Finalize()override;

		/*!
			@fn			�������̃Z�b�g
			@brief		�A�g���X�e�N�X�`���̕�������x��y�����ɂǂꂾ���������邩�w��
			@param[in]	������(x:x�����̌�,y:y�����̌�)
		*/
		void SetDevNum(const DirectX::XMINT2 divNum);

	private:
		DirectX::XMINT2 m_DivNum;	/*!< ������ */
		DirectX::XMINT2 m_Index;	/*!< �`�悷��e�N�X�`���ԍ� */
	};

}