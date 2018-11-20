/*
	@file	SoundManager.cpp
	@date	2018/03/02
	@author	�ԏ� �G�P
	@brief	�T�E���h�Ǘ��N���X
*/
#include "AudioDevice.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"

/*!
	@brief	���O���
	@detail	using�f�B���N�e�B�u
*/
using namespace D3D11::Sound;

/*!
	@brief	�R���X�g���N�^
*/
AudioDevice::AudioDevice()
{
}

/*!
	@brief	�f�X�g���N�^
*/
AudioDevice::~AudioDevice()
{
	Finalize();
}

/*!
	@brief	������
*/
HRESULT AudioDevice::Initialize()
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
void AudioDevice::Finalize()
{
	Release();

}

/*!
	@brief	�����o�̉��
*/
void AudioDevice::Release()
{
	if (m_pMasteringVoice) { m_pMasteringVoice->DestroyVoice(); m_pMasteringVoice = nullptr; }
	if (m_pXAudio2) { m_pXAudio2->Release(); m_pXAudio2 = nullptr; }
}