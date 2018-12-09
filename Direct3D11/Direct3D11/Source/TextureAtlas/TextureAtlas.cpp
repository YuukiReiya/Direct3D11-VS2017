#include "TextureAtlas.h"
#include "../MyGame.h"
#include "../Debug/Debug.h"

/*!
	@brief	���O���
	@detail	using�f�B���N�e�B�u
*/
using namespace API;
using namespace std;

/*!
	@brief	�R���X�g���N�^
	@detail	��������ITexture�̃R���X�g���N�^���Ăяo���f�t�H���g�l������
			�������͕`��O�ɐݒ肳��Ă��邱�Ƃ��O��Ȃ̂Ńf�t�H���g�ł͎Q�ƊO��ݒ肵�Ă����B
			�t�ɃC���f�b�N�X�͎w��Ȃ��ł��`��ł���悤�ɕ������������ۂ̍ŏ��l��ݒ肵�Ă���
*/
TextureAtlas::TextureAtlas() :ITexture(), m_DivNum({ -1,-1 }), m_Index({ 0,0 })
{
}

/*!
	@brief	�f�X�g���N�^
	@detail	Finalize�Ăяo��
*/
TextureAtlas::~TextureAtlas()
{
	Finalize();
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@param[in]	�ǂݍ��މ摜�̃p�X
	@param[in]	������(x,y)
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::TextureAtlas::Initialize(std::string filePath, const DirectX::XMFLOAT2 divNum)
{
	return Initialize(filePath, divNum, m_eTileMode, m_eFilterMode);
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂ƕ������̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	�\������摜�T�C�Y
				�������O�̉摜�T�C�Y�łȂ����Ƃɒ���
	@param[in]	������(x,y)
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::TextureAtlas::Initialize(std::string filePath, const DirectX::XMINT2 size, const DirectX::XMFLOAT2 divNum)
{
	HRESULT hr;

	/*! ������ */
	hr = Initialize(filePath, divNum);
	if (FAILED(hr)) {
		return hr;
	}

	/*! �T�C�Y�̐ݒ� */
	hr = SetSize(size) ? S_OK : E_FAIL;
	return hr;
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂ƕ������̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	������(x,y)
	@param[in]	�t�B���^�����O���[�h�̐ݒ�
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::TextureAtlas::Initialize(std::string filePath, const DirectX::XMFLOAT2 divNum, const FilteringMode filterMode)
{
	return Initialize(filePath, divNum, m_eTileMode, filterMode);
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂ƕ������̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	�\������摜�T�C�Y
				�������O�̉摜�T�C�Y�łȂ����Ƃɒ���
	@param[in]	������(x,y)
	@param[in]	�t�B���^�����O���[�h�̐ݒ�
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::TextureAtlas::Initialize(std::string filePath, const DirectX::XMINT2 size, const DirectX::XMFLOAT2 divNum, const FilteringMode filterMode)
{
	HRESULT hr;

	/*! ������ */
	hr = Initialize(filePath, divNum, filterMode);
	if (FAILED(hr)) {
		return hr;
	}

	/*! �T�C�Y�̐ݒ� */
	hr = SetSize(size) ? S_OK : E_FAIL;
	return hr;
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂ƕ������̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	������(x,y)
	@param[in]	�^�C�����O���[�h�̐ݒ�
	@param[in]	�t�B���^�����O���[�h�̐ݒ�
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::TextureAtlas::Initialize(std::string filePath, const DirectX::XMFLOAT2 divNum, const TileMode tileMode, const FilteringMode filterMode)
{
	HRESULT hr;

	/*! �摜�̃��[�h */
	hr = Load(filePath);
	if (FAILED(hr)) {
		std::string error = "\"" + filePath + "\" is not load in texture atlas!";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! �^�C�����O���[�h */
	m_eFilterMode	= filterMode;

	/*! �t�B���^�����O���[�h */
	m_eTileMode		= tileMode;

	/*! �^�C�����O�ƃt�B���^�����O��ݒ肵�A�T���v���[�X�e�[�g���쐬 */
	hr = SetTileAndFiltering(m_eTileMode, m_eFilterMode);
	if (FAILED(hr)) {
		std::string error = "\"" + filePath + "\" is not load in texture atlas!\n";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! �������̐ݒ� */
	m_DivNum = divNum;

	return S_OK;
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂ƕ������̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	�\������摜�T�C�Y
				�������O�̉摜�T�C�Y�łȂ����Ƃɒ���
	@param[in]	������(x,y)
	@param[in]	�^�C�����O���[�h�̐ݒ�
	@param[in]	�t�B���^�����O���[�h�̐ݒ�
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::TextureAtlas::Initialize(std::string filePath, const DirectX::XMINT2 size, const DirectX::XMFLOAT2 divNum, const TileMode tileMode, const FilteringMode filterMode)
{
	HRESULT hr;

	/*! �摜�̃��[�h */
	hr = Load(filePath);
	if (FAILED(hr)) {
		std::string error = "\"" + filePath + "\" is not load in texture atlas!";
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

	/*! �������̐ݒ� */
	m_DivNum = divNum;

	/*! �T�C�Y�̐ݒ� */
	hr = SetSize(size) ? S_OK : E_FAIL;

	return hr;
}

/*!
	@fn		�t�@�C�i���C�Y
	@brief	�j������
	@detail	�����o�̖����I�ȊJ��
*/
void API::TextureAtlas::Finalize()
{
	/*! ���ۃN���X�̃����o�̔j�� */
	ITexture::Finalize();
}

/*!
	@fn			�������̃Z�b�g
	@brief		�A�g���X�e�N�X�`���̕�������x��y�����ɂǂꂾ���������邩�w��
	@param[in]	������(x:x�����̌�,y:y�����̌�)
*/
void API::TextureAtlas::SetDevNum(const DirectX::XMFLOAT2 divNum)
{
#ifdef DEBUG_TEXTURE
	try
	{
		std::string error;

		/*! x�͈̔͊O�`�F�b�N */
		if (divNum.x <= 0) {
			error = "divNum.x is less than Zero!\n\
			divNum.x = " + std::to_string(divNum.x) + " <= 0";
			throw error;/*!< x�̕����ʐ���0�ȉ� */
		}

		/*! y�͈̔͊O�`�F�b�N */
		if (divNum.y <= 0) {
			error = "divNum.y is less than Zero!\n\
			divNum.y = " + std::to_string(divNum.y) + " <= 0";
			throw error;/*!< y�̕����ʐ���0�ȉ� */
		}

	}
	catch (std::string error)
	{
		ErrorLog(error);
	}
#endif
	m_DivNum = divNum;
}

/*!
	@fn			�`��C���f�b�N�X�̃Z�b�^�[
	@brief		�`�悷��A�g���X�e�N�X�`���̃C���f�b�N�X��ݒ�B
	@detail		�A�g���X�e�N�X�`���̕�������葽���l�͐ݒ�ł��܂���B
	@param[in]	�`�悵�����e�N�X�`���ԍ�
*/
void API::TextureAtlas::SetAtlasIndex(const DirectX::XMFLOAT2 index)
{
#ifdef DEBUG_TEXTURE
	std::string error;
	try
	{
		/*! x�͈̔͊O�`�F�b�N */
		if (index.x < 0) {
			error = "index.x is out-of-range\n\
			index.x = " + std::to_string(index.x) + "\n" +
			std::to_string(index.x) + " < 0";
			throw error;
		}

		/*! x�͈̔͊O�`�F�b�N */
		if (m_DivNum.x <= index.x) {
			error = "index.x is out-of-range\n\
			index.x = " + std::to_string(index.x) + "\n" +
			std::to_string(index.x) + " < DivNum.x-1 = " + std::to_string(m_DivNum.x - 1);
			throw error;
		}

		/*! y�͈̔͊O�`�F�b�N */
		if (index.y < 0) {
			error = "index.y is out-of-range\n\
			index.y = " + std::to_string(index.y) + "\n" +
			std::to_string(index.y) + " < 0";
			throw error;
		}

		/*! y�͈̔͊O�`�F�b�N */
		if (m_DivNum.y <= index.y) {
			error = "index.y is out-of-range\n\
			index.y = " + std::to_string(index.y) + "\n" +
			std::to_string(index.y) + " < DivNum.y-1 = " + std::to_string(m_DivNum.y - 1);
			throw error;
		}

	}
	catch (const std::string error)
	{
		ErrorLog(error);
		return;
	}
#endif // DEBUG_TEXTURE
	m_Index = index;
}
