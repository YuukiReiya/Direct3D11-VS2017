/*
	@file	Wav.h
	@date	2018/02/11
	@author	番場 宥輝
	@brief	Wavサウンド
*/
#pragma once
#include <string>
#include <XAudio2.h>
#include "../../ApplicationProgrammingInterface.h"

/*! API名前空間に含める */
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
