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
HRESULT API::TextureAtlas::Initialize(std::string filePath, const DirectX::XMINT2 divNum)
{
	return Initialize(filePath, divNum, m_eTileMode, m_eFilterMode);
}

/*!
	@fn			�C�j�V�����C�Y
	@brief		������
	@detail		�摜�̓ǂݍ��݂ƕ������̎w����s���A�T���v���[�X�e�[�g�̍쐬���s��
	@param[in]	�摜�̃p�X
	@param[in]	������(x,y)
	@param[in]	�^�C�����O���[�h�̐ݒ�
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::TextureAtlas::Initialize(std::string filePath, const DirectX::XMINT2 divNum, const TileMode tileMode)
{
	return Initialize(filePath, divNum, tileMode, m_eFilterMode);
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
HRESULT API::TextureAtlas::Initialize(std::string filePath, const DirectX::XMINT2 divNum, const FilteringMode filterMode)
{
	return Initialize(filePath, divNum, m_eTileMode, filterMode);
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
HRESULT API::TextureAtlas::Initialize(std::string filePath, const DirectX::XMINT2 divNum, const TileMode tileMode, const FilteringMode filterMode)
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
void API::TextureAtlas::SetDevNum(const DirectX::XMINT2 divNum)
{
#ifdef DEBUG_TEXTURE
	try
	{
		std::string error;

		/*! x�͈̔͊O�`�F�b�N */
		if (divNum.x <= 0) {
			error = "divNum.x is less than Zero!\n\
			divNum.x = " + std::to_string(divNum.x) + "< 0";
			throw error;/*!< x�̕����ʐ���0�ȉ� */
		}

		/*! y�͈̔͊O�`�F�b�N */
		if (divNum.y <= 0) {
			error = "divNum.y is less than Zero!\n\
			divNum.y = " + std::to_string(divNum.y) + "< 0";
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
