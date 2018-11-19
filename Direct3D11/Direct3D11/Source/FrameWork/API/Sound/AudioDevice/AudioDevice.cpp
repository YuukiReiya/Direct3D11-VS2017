/*
	@file	SoundManager.cpp
	@date	2018/03/02
	@author	番場 宥輝
	@brief	サウンド管理クラス
*/
#include <map>
#include "../../MemoryLeaks.h"
#include "SoundManager.h"
#include "../../MyGame.h"

/*!
	@var	Index
	@brief	連想配列で格納した
*/
std::map<std::string, int> Index;

/*!
	@brief	コンストラクタ
*/
SoundManager::SoundManager()
{
}

/*!
	@brief	デストラクタ
*/
SoundManager::~SoundManager()
{
	Finalize();
}

/*!
	@brief	初期化
*/
HRESULT SoundManager::Initialize()
{
	/*! COMライブラリの初期化 */
	if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED))) {
		if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED))) {
			ErrorLog("COM not Initialize");
			return E_FAIL;
		}
	}

	/*! XAudio2オブジェクト生成 */
	if (FAILED(XAudio2Create(&m_pXAudio2, 0))) {
		CoUninitialize();
		ErrorLog("IXAudio2 not instance");
		return E_FAIL;
	}

	/*! MasteringVoiceオブジェクト生成 */
	if (FAILED(m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice))) {
		CoUninitialize();
		ErrorLog("IXaudio2MasteringVoice not instance");
		return E_FAIL;
	}
	return S_OK;
}

/*!
	@brief	破棄
*/
void SoundManager::Finalize()
{
	Release();
}

/*!
	@brief	メンバの解放
*/
void SoundManager::Release()
{
	if (m_pMasteringVoice) { m_pMasteringVoice->DestroyVoice(); m_pMasteringVoice = nullptr; }
	if (m_pXAudio2) { m_pXAudio2->Release(); m_pXAudio2 = nullptr; }
}