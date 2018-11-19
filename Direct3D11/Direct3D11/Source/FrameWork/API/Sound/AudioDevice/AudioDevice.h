/*
	@file	SoundManager.h
	@date	2018/03/02
	@author	�ԏ� �G�P
	@brief	�T�E���h�Ǘ��N���X
*/
#pragma once
#pragma comment(lib,"Xaudio2.lib")

#include <string>
#include <XAudio2.h>

class SoundManager
{
public:
	~SoundManager();
	static SoundManager& GetInstance() {
		static SoundManager instance;
		return instance;
	}
	HRESULT Initialize(); 
	void Finalize();
	void Release();
	IXAudio2* GetXAudio2() { return m_pXAudio2; }
	IXAudio2MasteringVoice* GetMasterVoice() { return m_pMasteringVoice; }
private:
	SoundManager();
	IXAudio2*					m_pXAudio2;
	IXAudio2MasteringVoice*		m_pMasteringVoice;
};

