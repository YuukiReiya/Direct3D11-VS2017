/*
	@file	Wav.h
	@date	2018/02/11
	@author	�ԏ� �G�P
	@brief	Wav�T�E���h
*/
#pragma once
#include <string>
#include <XAudio2.h>
#include "../../ApplicationProgrammingInterface.h"

/*! API���O��ԂɊ܂߂� */
namespace API {

	class Wav
		:public API::IAPI
	{
	public:
		explicit Wav();
		~Wav();

		HRESULT API::IAPI::Initialize();
		void API::IAPI::Finalize();
		bool Load(std::string filePath);
		void Release();
		void Play(bool isLoop = false);
		void Stop();
		void Pause();
		void SetVolume(float vol);
		const float GetVolume()const;
	private:
		IXAudio2SourceVoice* m_pSourceVoice;
		BYTE* m_pWaveBuffer;
		DWORD m_dwWaveSize;
	};

};
