/*
	@file	SoundManager.cpp
	@date	2018/03/02
	@author	�ԏ� �G�P
	@brief	�T�E���h�Ǘ��N���X
*/
#include <map>
#include "../../MemoryLeaks.h"
#include "SoundManager.h"
#include "../../MyGame.h"

/*!
	@var	Index
	@brief	�A�z�z��Ŋi�[����
*/
std::map<std::string, int> Index;

/*!
	@brief	�R���X�g���N�^
*/
SoundManager::SoundManager()
{
}

/*!
	@brief	�f�X�g���N�^
*/
SoundManager::~SoundManager()
{
	Finalize();
}

/*!
	@brief	������
*/
HRESULT SoundManager::Initialize()
{
	/*! COM���C�u�����̏����� */
	if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED))) {
		if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED))) {
			ErrorLog("COM not Initialize");
			return E_FAIL;
		}
	}

	/*! XAudio2�I�u�W�F�N�g���� */
	if (FAILED(XAudio2Create(&m_pXAudio2, 0))) {
		CoUninitialize();
		ErrorLog("IXAudio2 not instance");
		return E_FAIL;
	}

	/*! MasteringVoice�I�u�W�F�N�g���� */
	if (FAILED(m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice))) {
		CoUninitialize();
		ErrorLog("IXaudio2MasteringVoice not instance");
		return E_FAIL;
	}
	return S_OK;
}

/*!
	@brief	�j��
*/
void SoundManager::Finalize()
{
	Release();
}

/*!
	@brief	�����o�̉��
*/
void SoundManager::Release()
{
	if (m_pMasteringVoice) { m_pMasteringVoice->DestroyVoice(); m_pMasteringVoice = nullptr; }
	if (m_pXAudio2) { m_pXAudio2->Release(); m_pXAudio2 = nullptr; }
}