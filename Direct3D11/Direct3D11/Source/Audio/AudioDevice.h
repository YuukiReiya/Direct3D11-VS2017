/*
	@file	AudioDevice.h
	@date	2018/11/19
	@author	番場 宥輝
	@brief	オーディオデバイスクラス
	@detail	XAudioを使ったAudioデバイスを管理
			シングルトン
*/
#pragma once
#pragma comment(lib,"Xaudio2.lib")

#include <XAudio2.h>
#include "../Singleton/Singleton.h"

/*! Direct3D11関連 */
namespace D3D11 {

	/*! サウンド関連の名前空間に含める */
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
