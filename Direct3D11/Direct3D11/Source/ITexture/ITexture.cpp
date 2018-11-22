#include "ITexture.h"
#include "../Direct3D11/Direct3D11.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
#include "../WindowsImagingComponent/WICTextureLoader.h"
#include "../Debug/Debug.h"

/*!
	@brief	���O���
	@detail	using�f�B���N�e�B�u
*/
using namespace D3D11;
using namespace DirectX;

/*!
	@brief	�R���X�g���N�^
	@detail	�����o�ϐ��̏��������s��
*/
API::ITexture::ITexture() :
	m_pShaderResourceView(nullptr),
	m_pSamplerState(nullptr),
	m_eTileMode(TileMode::Clamp),
	m_eFilterMode(FilteringMode::Trilinear)
{
}

/*!
	@brief	���z�f�X�g���N�^
	@detail	��f�X�g���N�^
*/
API::ITexture::~ITexture()
{
}

/*!
	@fn		�t�@�C�i���C�Y
	@brief	�j������
	@detail	�����o�̖����I�ȊJ��
			�h����Ń����o�������邱�Ƃ𓥂܂��A���z�֐��Ƃ��Ď���

*/
void API::ITexture::Finalize()
{
	//m_pShaderResourceView.Reset();
	//m_pSamplerState.Reset();
}

/*!
	@fn			�摜�T�C�Y�̃Z�b�^�[
	@brief		�ǂݍ��މ摜�̃T�C�Y�̐ݒ�
	@param[in]	�摜�T�C�Y
	@return		����:true ���s:false
*/
bool API::ITexture::SetSize(const DirectX::XMINT2 size)
{
#ifdef DEBUG_TEXTURE
	/*!
	*	�摜�T�C�Y�͒��_�����Ɏg�p����B
	*	�����Ő��������ꍇ�AUV�����]����̂���
	*	����͔��]���ĕ`�悷�邽�߂̊֐���p�ӂ��邽��
	*	�T�C�Y��0�ȉ����w�肵���ꍇ�ɃG���[��f���悤�ɂ���B
	*/
	try
	{
		std::string error;

		/*! �摜�̕����`�F�b�N */
		if (size.x <= 0) {
			error = "texture size.x is less than Zero!\n\
			size.x =" + std::to_string(size.x) + " <= 0";
			throw error;
		}

		/*! �摜�̍������`�F�b�N */
		if (size.y <= 0) {
			error = "texture size.x is less than Zero!\n\
			size.x =" + std::to_string(size.x) + " <= 0";
			throw error;
		}
	}
	catch (std::string& error)
	{
		ErrorLog(error);
		return false;
	}
#endif
	m_Size = size;
	return true;
}

/*!
	@fn			�^�C�����O���[�h�ƃt�B���^�����O���[�h�̃Z�b�^�[
	@brief		�^�C�����O���[�h�ƃt�B���^�����O���[�h�̐ݒ�
	@param[in]	�ݒ肷��^�C�����[�h
	@param[in]	�ݒ肷��t�B���^�����O(�A�h���b�V���O���[�h)
	@detail		�T���v���[�X�e�[�g���쐬
*/
HRESULT API::ITexture::SetTileAndFiltering(const TileMode tileMode, const FilteringMode filterMode)
{
	/*! �����̕ێ� */
	m_eTileMode = tileMode;
	m_eFilterMode = filterMode;

	/*! �T���v���[�X�e�[�g�ݒ� */
	D3D11_SAMPLER_DESC sd;
	SecureZeroMemory(&sd, sizeof(sd));
	sd.Filter = static_cast<D3D11_FILTER>(m_eFilterMode);				/*!< �t�B���^�����O */
	sd.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< �A�h���b�V���O���[�h */
	sd.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< �A�h���b�V���O���[�h */
	sd.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< �A�h���b�V���O���[�h */

	HRESULT hr;
	/*! �T���v���[�쐬 */
	hr = Direct3D11::GetInstance().GetDevice()->CreateSamplerState(
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

/*!
	@fn			�摜�̓ǂݍ���
	@brief		�摜�̓ǂݍ��݂��s��SRV���쐬
	@detail		�摜�f�[�^����SRV���쐬���A�����o�ϐ��Ƀo�C���h
	@param[in]	�ǂݍ��ރt�@�C���̃p�X
	@return		�ǂݎ�茋�� ����:S_OK  ���s:E_FAIL
*/
HRESULT API::ITexture::Load(std::string filePath)
{
	HRESULT hr;

	/*! 
		D3D11CompileFromFile�̈����̓}���`�o�C�g�Ȃ̂�
		�󂯎�����p�X���}���`�o�C�g�ɕϊ�
	*/
	auto cast = To_WString(filePath);
	auto path = const_cast<LPCWSTR>(cast.c_str());

	//!	���[�J���ϐ�
	Microsoft::WRL::ComPtr<ID3D11Resource> pResource = nullptr;

	/*! �e�N�X�`���쐬 */
	hr = CreateWICTextureFromFile(
		Direct3D11::GetInstance().GetDevice(),
		path,
		pResource.GetAddressOf(),
		m_pShaderResourceView.GetAddressOf()
	);

	/*! ���[�J���ϐ��̃������J�� */
	if (pResource.Get() != nullptr) {
		pResource.Reset();
	}
	if (FAILED(hr)) {
		std::string error = "\"" + filePath + "\" is not load in texture!";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! �ǂݍ��݂̐���I�� */
	return S_OK;
}
