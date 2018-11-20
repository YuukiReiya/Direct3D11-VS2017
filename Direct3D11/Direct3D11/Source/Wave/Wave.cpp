/*
	@file	Wave.h
	@date	2018/02/11
	@author	�ԏ� �G�P
	@brief	Wave�T�E���h
*/
#include "Wave.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
#include "../Audio/AudioDevice.h"

/*!
	@brief	���O���
	@detail	using�f�B���N�e�B�u
*/
using namespace API;
using namespace D3D11::Sound;

/*!
	@brief	�R���X�g���N�^
*/
Wave::Wave()
{
	Initialize();
}

/*!
	@brief	�f�X�g���N�^
*/
Wave::~Wave()
{
	Finalize();
}

/*!
	@brief	�C�j�V�����C�Y
*/
HRESULT Wave::Initialize() 
{
	SecureZeroMemory(this, sizeof(this));
	return S_OK;
}

/*!
	@brief		Wave�t�@�C���ǂݍ���
	@param[in]	�ǂݍ��ރt�@�C���̃p�X
*/
bool Wave::Load(std::string filePath)
{
	HMMIO hMmio = NULL;				/*!< Windows�}���`���f�B�AAPI�n���h�� */
	DWORD waveSize = 0;				/*!< Wave�f�[�^�T�C�Y */
	WAVEFORMATEX*	pFormat;		/*!< Wave�t�H�[�}�b�g */
	MMCKINFO		chunkInfo;		/*!< �`�����N��� */
	MMCKINFO		riffChunkInfo;	/*!< �ŏ㕔�`�����N */
	PCMWAVEFORMAT	pcmFormat;		/*!< PCM�t�H�[�}�b�g */

	/*! Wave�t�@�C�����̃w�b�_�[���ǂݍ��� */
	auto s_path = To_TString(filePath);
	const auto path = const_cast<LPTSTR>(s_path.c_str());
	hMmio = mmioOpen(path, NULL, MMIO_ALLOCBUF | MMIO_READ);

	/*! Wave�t�@�C���̓ǂݍ��ݎ��s */
	if (hMmio == NULL) {
		std::string error = "\"" + filePath + "\" is not load in sound!";
		ErrorLog(error);
		return false;
	}

	/*! �t�@�C���|�C���^��RIFF�`�����N�̐擪�ɃZ�b�g */
	mmioDescend(hMmio, &riffChunkInfo, NULL, 0);

	/*! �t�@�C���|�C���^��'f' 'm' 't' ' ' �`�����N�ɃZ�b�g���� */
	chunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hMmio, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK);

	/*! �t�H�[�}�b�g�ǂݍ��� */
	mmioRead(hMmio, (HPSTR)&pcmFormat, sizeof(pcmFormat));
	pFormat = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(pFormat, &pcmFormat, sizeof(pcmFormat));
	pFormat->cbSize = 0;
	mmioAscend(hMmio, &chunkInfo, 0);

	/*! ���f�[�^�ǂݍ��� */
	chunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hMmio, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK);
	waveSize = chunkInfo.cksize;
	m_pWaveBuffer = new BYTE[waveSize];
	DWORD offset = chunkInfo.dwDataOffset;
	mmioRead(hMmio, (char*)m_pWaveBuffer, waveSize);

	/*! �I�[�f�B�I�f�o�C�X�̎Q�� */
	auto& manager = AudioDevice::GetInstance();

	/*! �\�[�X�{�C�X�Ƀf�[�^�l�ߍ��� */
	XAUDIO2_SEND_DESCRIPTOR sendDescriptor;
	sendDescriptor.Flags = XAUDIO2_SEND_USEFILTER;
	sendDescriptor.pOutputVoice = manager.GetMasterVoice();
	const XAUDIO2_VOICE_SENDS sendList = { 1,&sendDescriptor };

	/*! �\�[�X�{�C�X�쐬 */
	HRESULT hr = manager.GetXAudio2()->CreateSourceVoice(&m_pSourceVoice, pFormat, 0, 2.0f, NULL, &sendList);

	SAFE_DELETE(pFormat);

	if (FAILED(hr)) {
		ErrorLog("SourceVoice is not create!");
		return false;
	}
	m_dwWaveSize = waveSize;

	return true;
}

/*!
	@brief	�t�@�C�i���C�Y
*/
void Wave::Finalize() 
{
	Release();/*!< �������J�� */
}

/*!
	@brief	���
*/
void Wave::Release()
{
	SAFE_DELETE(m_pWaveBuffer);
}

/*!
	@brief		�Đ�
	@detail		�ꎞ��~�A��~���"�Đ�"��������g��
	@param[in]	���[�v�t���O
*/
void Wave::Play(bool isLoop)
{
	/*! �T�u�~�b�g */
	XAUDIO2_BUFFER buffer = { 0 };
	SecureZeroMemory(&buffer, sizeof(buffer));
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = m_dwWaveSize;
	buffer.pAudioData = m_pWaveBuffer;
	buffer.PlayBegin = 0;	/*!< �Đ������o�b�t�@�̍ŏ��̃T���v�� */
	buffer.PlayLength = 0;	/*!< �T�E���h�̃o�b�t�@�S�� */
	if (isLoop) {

		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else {

		buffer.LoopBegin = XAUDIO2_NO_LOOP_REGION;
		buffer.LoopCount = 0;
	}
	HRESULT hr = m_pSourceVoice->SubmitSourceBuffer(&buffer);
	if (FAILED(hr)) {
		std::string error = "Wave is not played!";
		ErrorLog(error);
		return;
	}
	m_pSourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
}

/*!
	@brief	��~
*/
void Wave::Stop()
{
	m_pSourceVoice->Stop(0, XAUDIO2_COMMIT_NOW);
	m_pSourceVoice->FlushSourceBuffers();
}

/*!
	@brief	�ꎞ��~
*/
void API::Wave::Pause()
{
	m_pSourceVoice->Stop(0, XAUDIO2_COMMIT_NOW);
}


/*!
	@brief		���ʕύX
	@detail		�͈� 0�`1
	@param[in]	�ݒ肷�鉹��
*/
void API::Wave::SetVolume(float vol)
{
	m_pSourceVoice->SetVolume(vol);
}

const float API::Wave::GetVolume() const
{
	return 0.0f;
}

