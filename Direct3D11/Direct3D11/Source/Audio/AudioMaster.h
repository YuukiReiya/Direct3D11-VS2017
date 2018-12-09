/*
	@file	AudioMaster.h
	@date	2018/11/19
	@author	�ԏ� �G�P
	@brief	�I�[�f�B�I�f�o�C�X�N���X
	@detail	XAudio���g����Audio�f�o�C�X���Ǘ�
			�V���O���g��
*/
#pragma once
#pragma comment(lib,"Xaudio2.lib")

#include <XAudio2.h>
#include "../Singleton/Singleton.h"

/*! Direct3D11�֘A */
namespace D3D11 {

	/*! �T�E���h�֘A�̖��O��ԂɊ܂߂� */
	namespace Sound {

		class AudioMaster
			:public Singleton<AudioMaster>
		{
		public:
			/*!
				@brief	�f�X�g���N�^
			*/
			~AudioMaster();

			/*!
				@fn		�C�j�V�����C�Y
				@brief	������
				@return	S_OK:���� E_FAIL:���s
			*/
			HRESULT Initialize();

			/*!
				@fn		�t�@�C�i���C�Y
				@brief	�j������
				@detail	�����o�̖����I�ȉ���ƃ����o�̏�����
			*/
			void Finalize();

			/*!
				@fn		�I�[�f�B�I�f�o�C�X�̃Q�b�^�[
				@brief	�I�[�f�B�I�f�o�C�X�̎擾
				@return	�I�[�f�B�I�f�o�C�X
			*/
			IXAudio2* GetXAudio2() { return m_pXAudio2; }

			/*!
				@fn		�}�X�^�����O�{�C�X�̃Q�b�^�[
				@brief	�}�X�^�����O�{�C�X�̎擾
				@return	�}�X�^�����O�{�C�X
			*/
			IXAudio2MasteringVoice* GetMasterVoice() { return m_pMasteringVoice; }
		private:
			/*!
				@brief	�R���X�g���N�^
			*/
			AudioMaster();

			/*!
				@brief	�V���O���g���f�U�C���p�^�[���̃e���v���[�g�p��
			*/
			friend class Singleton<AudioMaster>;

			IXAudio2*					m_pXAudio2;			/*!< �I�[�f�B�I */
			IXAudio2MasteringVoice*		m_pMasteringVoice;	/*!< �}�X�^�����O�{�C�X */
		};

	}
}
