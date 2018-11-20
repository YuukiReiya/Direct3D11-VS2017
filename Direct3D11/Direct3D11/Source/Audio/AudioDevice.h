/*
	@file	AudioDevice.h
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

		class AudioDevice
			:public Singleton<AudioDevice>
		{
		public:
			~AudioDevice();
			HRESULT Initialize();
			void Finalize();
			void Release();
			IXAudio2* GetXAudio2() { return m_pXAudio2; }
			IXAudio2MasteringVoice* GetMasterVoice() { return m_pMasteringVoice; }
		private:
			AudioDevice();
			friend class Singleton<AudioDevice>;

			IXAudio2*					m_pXAudio2;
			IXAudio2MasteringVoice*		m_pMasteringVoice;
		};

	}
}
