/*
	@file	Wave.h
	@date	2018/02/11
	@author	�ԏ� �G�P
	@brief	Wave�T�E���h
	@detail	.wav�g���q�̉����Đ�
*/
#pragma once
#include <string>
#include <XAudio2.h>

/*! API���O��ԂɊ܂߂� */
namespace API {

	class Wave
	{
	public:
		/*!
			@brief	�R���X�g���N�^
		*/
		explicit Wave();

		/*!
			@brief	�f�X�g���N�^
		*/
		~Wave();

		/*!
			@fn		�C�j�V�����C�Y
			@brief	������
			@detail	�Z�L���A�[��������
			@return	S_OK:���� E_FAIL:���s
		*/
		HRESULT Initialize();

		/*!
			@fn		�t�@�C�i���C�Y
			@brief	�j������
			@detail	�����o�̖����I�ȉ��
		*/
		void Finalize();

		/*!
			@fn			���[�h
			@brief		�t�@�C���̃��[�h
			@detail		Wave�t�@�C���ǂݍ���
			@param[in]	�ǂݍ��ރt�@�C���̃p�X
			@return		true:���� false:���s
		*/
		bool Load(std::string filePath);

		/*!
			@fn			�v���C
			@brief		���̍Đ�
			@detail		�ꎞ��~�A��~���"�Đ�"��������g��
			@param[in]	���[�v�t���O
		*/
		void Play(bool isLoop = false);

		/*!
			@fn		�X�g�b�v
			@brief	���̒�~
		*/
		void Stop();

		/*!
			@fn		�|�[�Y
			@brief	���̈ꎞ��~
		*/
		void Pause();

		/*!
			@fn			�{�����[���̃Z�b�g
			@brief		���̉��ʂ�ݒ�
			@detail		�͈� 0�`1
			@param[in]	�ݒ肷�鉹��
		*/
		void SetVolume(float vol);
	private:
		IXAudio2SourceVoice* m_pSourceVoice;
		BYTE* m_pWaveBuffer;
		DWORD m_dwWaveSize;
	};

};
