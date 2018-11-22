#include "Texture.h"
#include "../Direct3D11/Direct3D11.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
#include "../WindowsImagingComponent/WICTextureLoader.h"

/*!
	@brief	���O���
	@detail	using�f�B���N�e�B�u
*/
using namespace D3D11;
using namespace DirectX;


/*!
	@brief	�R���X�g���N�^
	@detail	��������ITexture�̃R���X�g���N�^���Ăяo���f�t�H���g�l������
*/
API::Texture::Texture() :ITexture()
{

}

/*!
	@brief	�f�X�g���N�^
	@detail	Finalize�Ăяo��
*/
API::Texture::~Texture() 
{
	Finalize();
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@param[in]	�摜�̃p�X
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Texture::Initialize(std::string filePath)
{
	return Initialize(filePath, m_eTileMode, m_eFilterMode);
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@param[in]	�摜�̃p�X
	@param[in]	�摜�T�C�Y
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Texture::Initialize(std::string filePath, const DirectX::XMINT2 size)
{
	return Initialize(filePath, size, m_eTileMode, m_eFilterMode);
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂ƃT���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	�^�C�����O���[�h�̐ݒ�
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Texture::Initialize(std::string filePath, const TileMode tileMode)
{
	return Initialize(filePath, tileMode, m_eFilterMode);
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂Ɖ摜�T�C�Y�̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	�摜�T�C�Y
	@param[in]	�^�C�����O���[�h�̐ݒ�
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Texture::Initialize(std::string filePath, const DirectX::XMINT2 size, const TileMode tileMode)
{
	return Initialize(filePath, size, tileMode, m_eFilterMode);
}


/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂Ɖ摜�T�C�Y�̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	�t�B���^�����O���[�h�̐ݒ�
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Texture::Initialize(std::string filePath, const FilteringMode filterMode)
{
	return Initialize(filePath, m_eTileMode, filterMode);
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂Ɖ摜�T�C�Y�̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	�摜�T�C�Y
	@param[in]	�t�B���^�����O���[�h�̐ݒ�
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Texture::Initialize(std::string filePath, const DirectX::XMINT2 size, const FilteringMode filterMode)
{
	return Initialize(filePath, size, m_eTileMode, filterMode);
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂Ɖ摜�T�C�Y�̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	�^�C�����O���[�h�̐ݒ�
	@param[in]	�t�B���^�����O���[�h�̐ݒ�
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Texture::Initialize(std::string filePath, const TileMode tileMode, const FilteringMode filterMode)
{
	HRESULT hr;

	/*! �摜�̃��[�h */
	hr = Load(filePath);
	if (FAILED(hr)) {
		std::string error = "\"" + filePath + "\" is not load in texture!";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! �^�C�����O���[�h */
	m_eFilterMode = filterMode;

	/*! �t�B���^�����O���[�h */
	m_eTileMode = tileMode;

	/*! �^�C�����O�ƃt�B���^�����O��ݒ肵�A�T���v���[�X�e�[�g���쐬 */
	hr = SetTileAndFiltering(m_eTileMode, m_eFilterMode);
	if (FAILED(hr)) {
		std::string error = "\"" + filePath + "\" is not load in texture atlas!\n";
		ErrorLog(error);
		return E_FAIL;
	}

	return S_OK;
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂Ɖ摜�T�C�Y�̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	�摜�T�C�Y
	@param[in]	�^�C�����O���[�h�̐ݒ�
	@param[in]	�t�B���^�����O���[�h�̐ݒ�
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Texture::Initialize(std::string filePath, const DirectX::XMINT2 size, const TileMode tileMode, const FilteringMode filterMode)
{
	HRESULT hr;

	/*! ������ */
	hr = Initialize(filePath, tileMode, filterMode);
	if (FAILED(hr)) {
		return hr;
	}

	/*! �T�C�Y�̐ݒ� */
	hr = SetSize(size) ? S_OK : E_FAIL;
	return hr;
}

/*!
	@fn		�t�@�C�i���C�Y
	@brief	�j������
	@detail	�����o�̖����I�ȊJ��
*/
void API::Texture::Finalize()
{
	/*! ���ۃN���X�̃����o�̔j�� */
	ITexture::Finalize();
}
