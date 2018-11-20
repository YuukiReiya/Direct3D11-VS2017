#include "Texture.h"
#include "../Direct3D11/Direct3D11.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
#include "../WindowsImagingComponent/WICTextureLoader.h"

/*!
	wincodec.h��CreateDecoderFromFilename�̈������}���`�o�C�g������̈����̂���
	UNICODE�ݒ�ł��}���`�o�C�g�������g���K�v������
*/

/*!
	@brief	���O���
	@detail	using�f�B���N�e�B�u
*/
using namespace D3D11;
using namespace API;
using namespace DirectX;


/*!
	@brief	�R���X�g���N�^
*/
Texture::Texture()
{
	SecureZeroMemory(this, sizeof(this));
	m_pSamplerState		= nullptr;
	m_pResorceTexture	= nullptr;
	m_eTileMode			= TileMode::Clamp;
	m_eFilteringMode	= FilteringMode::Trilinear;
}

/*!
	@brief	�f�X�g���N�^
*/
Texture::~Texture()
{
	Finalize();
}

/*!
	@brief	������
	@detail	���ݐݒ肳��Ă���^�C�����O���[�h�ƃt�B���^�����O���[�h��ݒ肷��
*/
HRESULT Texture::Initialize() 
{
	return SetTileAndFiltering(m_eTileMode, m_eFilteringMode);
}

/*!
	@brief		������
	@detail		�^�C�����O���[�h��ύX���A�T���v���[�����Ȃ���
	@param[in]	�ݒ肷��^�C�����O���[�h
*/
HRESULT Texture::Initialize(TileMode tileMode)
{
	return SetTileAndFiltering(tileMode, m_eFilteringMode);
}

/*!
	@brief		������
	@detail		�t�B���^�����O���[�h��ύX���A�T���v���[�����Ȃ���
	@param[in]	�ݒ肷��t�B���^�����O���[�h
*/
HRESULT Texture::Initialize(FilteringMode filteringMode)
{
	return SetTileAndFiltering(m_eTileMode, filteringMode);
}

/*!
	@brief		������
	@detail		�^�C�����O���[�h�ƃt�B���^�����O���[�h��ύX���A�T���v���[�����Ȃ���
	@param[in]	�ݒ肷��^�C�����O���[�h
	@param[in]	�ݒ肷��t�B���^�����O���[�h
*/
HRESULT Texture::Initialize(TileMode tileMode, FilteringMode filteringMode)
{
	return SetTileAndFiltering(tileMode, filteringMode);
}

/*!
	@brief		������
	@detail		�e�N�X�`���̃��[�h�ƃT���v���[�̐��������˂�
	@param[in]	���[�h����e�N�X�`���̃t�@�C���p�X
	@param[in]	���[�h����摜�̃T�C�Y
*/
HRESULT API::Texture::Initialize(std::string filePath, DirectX::XMINT2 size)
{
	return Load(filePath, size);
}

/*!
	@brief	�e�N�X�`���f�[�^�̓ǂݍ���
	@detail	�e�N�X�`���f�[�^�̖����I�ȃ��[�h�֐�
*/
HRESULT Texture::Load(std::string filePath, DirectX::XMINT2 size)
{
	HRESULT hr;

	/*! UNICODE�ƃ}���`�o�C�g������̗��Ή��p�R�[�h */
	//auto s_path = To_TString(filePath);
	//const auto path = const_cast<LPTSTR>(s_path.c_str());

	/*! D3D11CompileFromFile�̈����̓}���`�o�C�g */
	auto tmp = To_WString(filePath);
	auto path = const_cast<LPCWSTR>(tmp.c_str());


	m_Size = size;

	/*! �T���v���[����������Ă��Ȃ���ΐ������� */
	if (!m_pSamplerState) {
		SetTileAndFiltering(m_eTileMode, m_eFilteringMode);
	}

	/*! ���[�J���ϐ� */
	ID3D11Resource* pResource = nullptr;

	/*! �e�N�X�`���̐��� */
	hr = CreateWICTextureFromFile(
		Direct3D11::GetInstance().GetDevice(),
		path,
		&pResource,
		m_pResorceTexture.GetAddressOf()
	);

	/*! ���[�J���ϐ��̃������J�� */
	if (pResource != nullptr) {
		pResource->Release();
	}
	if (FAILED(hr)) {
		std::string error = "\"" + filePath + "\" is not load in texture!";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! �ǂݍ��݂̐���I�� */
	return S_OK;
}

/*!
	@brief	�t�@�C�i���C�Y
	@detail	COM�|�C���^���g�p���Ă���̂�Reset�̖����I�ȌĂяo��
*/
void Texture::Finalize()
{
	m_pSamplerState.Reset();
	m_pResorceTexture.Reset();
}

/*!
	@brief		�^�C�����O���[�h�ƃt�B���^�����O���[�h�̐ݒ�
	@param[in]	�ݒ肷��^�C�����[�h
	@param[in]	�ݒ肷��t�B���^�����O(�A�h���b�V���O���[�h)
	@detail		�T���v���[�X�e�[�g�̍쐬
*/
HRESULT Texture::SetTileAndFiltering(TileMode tile, FilteringMode filter)
{
	/*! �����̕ێ� */
	m_eTileMode			= tile;
	m_eFilteringMode	= filter;

	/*! �T���v���[�X�e�[�g�ݒ� */
	D3D11_SAMPLER_DESC sd;
	SecureZeroMemory(&sd, sizeof(sd));
	sd.Filter = static_cast<D3D11_FILTER>(m_eFilteringMode);			/*!< �t�B���^�����O */
	sd.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< �A�h���b�V���O���[�h */
	sd.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< �A�h���b�V���O���[�h */
	sd.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< �A�h���b�V���O���[�h */

	HRESULT hr;
	/*! �T���v���[�쐬 */
	hr= Direct3D11::GetInstance().GetDevice()->CreateSamplerState(
		&sd,
		m_pSamplerState.GetAddressOf()
	);
	if (FAILED(hr)) {
		std::string error = "Sampler state is not created!";
		ErrorLog(error);
		return E_FAIL;
	}
	return S_OK;
}
