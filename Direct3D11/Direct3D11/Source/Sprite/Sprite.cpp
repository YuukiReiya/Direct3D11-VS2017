/*
	@file	Sprite.h
	@date	2018/03/04
	@author	�ԏ� �G�P
	@brief	�X�v���C�g
	@detail	�Q�l:http://zerogram.info/?p=2029
*/
#include <D3D11.h>
#include "Sprite.h"
#include "../Direct3D11/Direct3D11.h"
#include "../Debug/Debug.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
#include "../Camera/Camera.h"
#include "../ShaderManager/ShaderManager.h"

/*!
	@brief	���O���
	@detail	using�f�B���N�e�B�u
*/
using namespace D3D11;
using namespace D3D11::Graphic;
using namespace API;

/*!
	@def	�萔�錾
*/
const float Sprite::c_NormalizeSize = 100.0f;	/*!< �X�P�[����1�̎��̊�ƂȂ�T�C�Y(100�~100���傫���̊) */
const float Sprite::c_ScaleZ	= 0;			/*!< Z�����̃X�P�[���͏�Ƀ[���Ōv�Z���� */
const float Sprite::c_VertexZ	= 0;			/*!< �|���̒��_���W��z�l */

/*!
	@brief	�R���X�g���N�^
*/
Sprite::Sprite()
{
	m_pVertexBuffer		= nullptr;
	m_pBlendState		= nullptr;
	m_Pos = { 0,0,0 };
	m_Scale = { 1,1 ,0 };
	m_Rot = {0,0,0};
	m_Size = { -1,-1 };
	m_StencilMask = 0xffffffff;
}

/*!
	@brief	�f�X�g���N�^
*/
Sprite::~Sprite()
{
	Finalize();
}

/*!
	@fn		�C�j�V�����C�Y
	@brief	������
	@detail	�u�����h�X�e�[�g�̍쐬���s��
*/
HRESULT Sprite::Initialize()
{
	HRESULT hr;

	/*!
	��
	SRC:�\�[�X(���ꂩ��`�悷��s�N�Z���̐F)
	DEST:�f�B�X�g�l�[�V����(�����_�����O�^�[�Q�b�g�ɕ`�悳��Ă���s�N�Z���̐F)
	
	�ŏI�I�ȕ`��F�͈ȉ��́u�����֐��v�ɂ���Č��܂�
	
		SRC �~ �u�����f�B���O�W�� �{ DEST �~ �u�����f�B���O�W��
	
		SRCALPHA:	 SRC �̃��l
		INVSRCALPHA: 1 - SRC �̃��l
		DESTALPHA:	 DEST�̃��l
	*/

	/*! ���u�����h */
	/*! ���e�X�g�ݒ� */
	D3D11_BLEND_DESC bd;
	SecureZeroMemory(&bd, sizeof(bd));

	/*!< �u�����h�̗L���E���� */
	bd.RenderTarget[0].BlendEnable		= true;

	/*! �u�����f�B���O�W���̐ݒ� */
	bd.RenderTarget[0].SrcBlend			= D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend		= D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;

	//
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;


	/*! �u�����h�I�v�V���� */
	bd.RenderTarget[0].BlendOp			= D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha	= D3D11_BLEND::D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha	= D3D11_BLEND::D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha		= D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;


	//
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;

	/*! �A���`�G�C���A�X���� */
	//bd.AlphaToCoverageEnable = true;	/*!< �؂����������ɑ΂���A���`�G�C���A�X�����̗L�� */
	bd.IndependentBlendEnable = false;

	/*! �u�����h�X�e�[�g�̍쐬 */
	hr = Direct3D11::GetInstance().GetDevice()->CreateBlendState(
		&bd,
		m_pBlendState.GetAddressOf()
	);
	if (FAILED(hr)) {
		std::string error = "BlendState is not create!";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! �u�����h�X�e�[�g�̐ݒ� */
	Direct3D11::GetInstance().GetDeviceContext()->OMSetBlendState(
		m_pBlendState.Get(),
		NULL,
		m_StencilMask
	);

	return S_OK;
}

/*!
	@fn		�t�@�C�i���C�Y
	@brief	�j������
	@detail	�����o�̖����I�ȉ���ƃ����o�̏�����
*/
void Sprite::Finalize()
{
	/*! �����o�̏����� */
	m_Pos = { 0,0,0 };
	m_Scale = { 1,1 ,0 };
	m_Rot = { 0,0,0 };
	m_Size = { -1,-1 };
	m_StencilMask = 0xffffffff;

	/*! �J�� */
	Release();
}

/*!
	@fn		�����[�X
	@brief	�������
	@detail	�����o�̖����I�ȉ��
*/
void Sprite::Release()
{
	m_pVertexBuffer.Reset();
	m_pBlendState.Reset();
}

/*!
	@fn			�u�����h�X�e�[�g�̍쐬
	@brief		�쐬�����u�����h�X�e�[�g�͕`�掞�Ƀo�C���h�����
	@detail		�����o�̃u�����h�X�e�[�g����ύX
	@param[in]	���Ȓ�`�̃u�����h�X�e�[�g
*/
void Sprite::CreateAlphaBlendState(D3D11_BLEND_DESC desc)
{
	HRESULT hr;

	/*! �������J�� */
	m_pBlendState.Reset();

	/*! �u�����h�X�e�[�g�쐬 */  
	hr = Direct3D11::GetInstance().GetDevice()->CreateBlendState(
		&desc,
		m_pBlendState.GetAddressOf()
	);
	if (FAILED(hr)) {
		std::string error = "BlendState is not create!";
		ErrorLog(error);
	}
}

/*!
	@fn			�e�N�X�`���̕`��
	@brief		�V���v���e�N�X�`���̕`��
	@detail		map,unmap���g���ăe�N�X�`���}�b�s���O������`��
	@param[in]	�`�悷��e�N�X�`��
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Sprite::Render(Texture * pTexture)
{
	HRESULT hr;

	const auto size = pTexture->GetSize();

	/*! �قȂ�T�C�Y�̃e�N�X�`�����n���ꂽ�璸�_���� */
	if (m_Size.x != size.x || m_Size.y != size.y) {

		/*! ���_�o�b�t�@���� */
		hr = CreateVertex(size);
		if (FAILED(hr)) {
			std::string error = "Create vertex is failed!";
			ErrorLog(error);
			return E_FAIL;
		}

		/*! �e�N�X�`���̃T�C�Y���L���b�V�����Ă��� */
		m_Size = size;
	}

	/*! �g�|���W�[�Z�b�g */
	Direct3D11::GetInstance().GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
	);

	auto shaderData = ShaderManager::GetInstance().GetShaderData(ShaderManager::c_szSimpleTextureShader);

	/*! ���_�C���v�b�g���C�A�E�g�Z�b�g */
	Direct3D11::GetInstance().GetDeviceContext()->IASetInputLayout(
		shaderData->m_pVertexLayout.Get()
	);

	/*! �V�F�[�_�[�̓o�^ */
	Direct3D11::GetInstance().GetDeviceContext()->VSSetShader(
		shaderData->m_pVertexShader.Get(),
		NULL,
		NULL
	);
	Direct3D11::GetInstance().GetDeviceContext()->PSSetShader(
		shaderData->m_pPixelShader.Get(),
		NULL,
		NULL
	);

	/*! �R���X�^���g�o�b�t�@�̓o�^ */
	Direct3D11::GetInstance().GetDeviceContext()->VSSetConstantBuffers(
		0,
		1,
		shaderData->m_pConstantBuffer.GetAddressOf()
	);
	Direct3D11::GetInstance().GetDeviceContext()->PSSetConstantBuffers(
		0,
		1,
		shaderData->m_pConstantBuffer.GetAddressOf()
	);

	/*! �T���v���[�擾 */
	auto ppSampler = pTexture->GetSamplerState();

	/*! SRV�擾 */
	auto ppSRV = pTexture->GetShaderResourceView();

	/*! �e�N�X�`�� */
	Direct3D11::GetInstance().GetDeviceContext()->PSSetSamplers(
		0,
		1,
		ppSampler
	);
	Direct3D11::GetInstance().GetDeviceContext()->PSSetShaderResources(
		0,
		1,
		ppSRV
	);

	/*! ���W�ϊ� */
	DirectX::XMMATRIX mWorld, mTran, mRot, mScale;
	mWorld	= DirectX::XMMatrixIdentity();
	mTran	= DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	mRot	= DirectX::XMMatrixRotationRollPitchYaw(m_Rot.x, m_Rot.y, m_Rot.z);
	mScale	= DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, c_ScaleZ);

	/*! ���[���h�ϊ� */
	mWorld = mScale * mRot * mTran;

	/*! �}�b�s���O�p�ϐ��錾 */
	D3D11_MAPPED_SUBRESOURCE pData;
	SecureZeroMemory(&pData, sizeof(pData));

	/*! �V�F�[�_�[���ɓn���R���X�^���g�o�b�t�@�錾 */
	SpriteShaderBuffer cb;
	SecureZeroMemory(&cb, sizeof(cb));

	/*! �o�b�t�@�ւ̃A�N�Z�X����(��������) */
	hr = Direct3D11::GetInstance().GetDeviceContext()->Map(
		shaderData->m_pConstantBuffer.Get(),
		NULL,
		D3D11_MAP_WRITE_DISCARD,
		NULL,
		&pData
	);
	if (FAILED(hr)) {
		std::string error = "Texture mapping is failed!";
		ErrorLog(error);
		Direct3D11::GetInstance().GetDeviceContext()->Unmap(shaderData->m_pConstantBuffer.Get(), NULL);/*!< �A�N�Z�X������Ĕ����� */
		return E_FAIL;
	}

	auto camera = &Camera::GetInstance();
	const Color& color = pTexture->m_Color;
	/*! �R���X�^���g�o�b�t�@�Ƀf�[�^�𑗂� */
	DirectX::XMMATRIX m = mWorld*camera->GetViewMatrix()*camera->GetProjMatrix();
	cb.m_WVP = m;						/*!< ���[���h�s�� */
	cb.m_DivNum = { 1,1 };
	cb.m_Index = { 0,0 };
	cb.m_Color = color.GetRGBA();
	
	/*! �������R�s�[ */
	memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
	
	/*! �A�N�Z�X���I�� */
	Direct3D11::GetInstance().GetDeviceContext()->Unmap(
		shaderData->m_pConstantBuffer.Get(), 
		NULL
	);
	
	/*! ���_�o�b�t�@�Z�b�g */
	uint32_t stride = sizeof(SpriteVertex);
	uint32_t offset = 0;
	Direct3D11::GetInstance().GetDeviceContext()->IASetVertexBuffers(
		0,
		1,
		m_pVertexBuffer.GetAddressOf(),
		&stride,
		&offset
	);

	/*! �u�����h�X�e�[�g�̐ݒ� */
	Direct3D11::GetInstance().GetDeviceContext()->OMSetBlendState(
		m_pBlendState.Get(),
		NULL,
		m_StencilMask
	);

	/*! �`�� */
	Direct3D11::GetInstance().GetDeviceContext()->Draw(
		4,		/*!< ���_��(�|���S���Ȃ̂Œ��_����4��) */
		NULL
	);

	return S_OK;
}

/*!
	@fn			�e�N�X�`���̕`��
	@brief		�A�g���X�e�N�X�`���̕`��
	@detail		SubResource���g����UpdateSubResource������`��
	@param[in]	�`�悷��e�N�X�`��
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Sprite::Render(TextureAtlas * pTexture)
{
	
	HRESULT hr;

	auto size = pTexture->GetSize();

	/*! ���_�o�b�t�@���� */
	hr = CreateVertex(size);
	if (FAILED(hr)) {
		std::string error = "Create vertex is failed!";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! �e�N�X�`���̃T�C�Y���L���b�V�����Ă��� */
	m_Size = size;

	/*! �g�|���W�[�Z�b�g */
	Direct3D11::GetInstance().GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
	);

	auto shaderData = ShaderManager::GetInstance().GetShaderData(ShaderManager::c_szTextureAtlasShader);

	/*! ���_�C���v�b�g���C�A�E�g�Z�b�g */
	Direct3D11::GetInstance().GetDeviceContext()->IASetInputLayout(
		shaderData->m_pVertexLayout.Get()
	);

	/*! �V�F�[�_�[�̓o�^ */
	Direct3D11::GetInstance().GetDeviceContext()->VSSetShader(
		shaderData->m_pVertexShader.Get(),
		NULL,
		NULL
	);
	Direct3D11::GetInstance().GetDeviceContext()->PSSetShader(
		shaderData->m_pPixelShader.Get(),
		NULL,
		NULL
	);

	/*! �R���X�^���g�o�b�t�@�̓o�^ */
	Direct3D11::GetInstance().GetDeviceContext()->VSSetConstantBuffers(
		0,
		1,
		shaderData->m_pConstantBuffer.GetAddressOf()
	);
	Direct3D11::GetInstance().GetDeviceContext()->PSSetConstantBuffers(
		0,
		1,
		shaderData->m_pConstantBuffer.GetAddressOf()
	);

	/*! �T���v���[�擾 */
	auto ppSampler = pTexture->GetSamplerState();

	/*! SRV�擾 */
	auto ppSRV = pTexture->GetShaderResourceView();

	/*! �e�N�X�`�� */
	Direct3D11::GetInstance().GetDeviceContext()->PSSetSamplers(
		0,
		1,
		ppSampler
	);
	Direct3D11::GetInstance().GetDeviceContext()->PSSetShaderResources(
		0,
		1,
		ppSRV
	);

	/*! ���W�ϊ� */
	DirectX::XMMATRIX mWorld, mTran, mRot, mScale;
	mWorld	= DirectX::XMMatrixIdentity();
	mTran	= DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	mRot	= DirectX::XMMatrixRotationRollPitchYaw(m_Rot.x, m_Rot.y, m_Rot.z);
	mScale	= DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, c_ScaleZ);

	/*! ���[���h�ϊ� */
	mWorld = mScale * mRot * mTran;

	/*! �V�F�[�_�[���ɓn���R���X�^���g�o�b�t�@�錾 */
	SpriteShaderBuffer cb;
	SecureZeroMemory(&cb, sizeof(cb));

	/*! �R���X�^���g�o�b�t�@�̃f�[�^�������� */
	auto camera = &Camera::GetInstance();
	const Color& color = pTexture->m_Color;
	DirectX::XMMATRIX m = mWorld * camera->GetViewMatrix()*camera->GetProjMatrix();
	
	cb.m_WVP		= m;				/*!< ���[���h�s�� */
	cb.m_DivNum		= pTexture->GetDivNum();
	cb.m_Index		= pTexture->GetAtlasIndex();
	cb.m_Color		= color.GetRGBA();

	/*! UpdateSubResource */
	Direct3D11::GetInstance().GetDeviceContext()->UpdateSubresource(
		shaderData->m_pConstantBuffer.Get(),
		NULL,
		nullptr,
		&cb,
		NULL,
		NULL
	);



	/*! �u�����h�X�e�[�g�̐ݒ� */
	Direct3D11::GetInstance().GetDeviceContext()->OMSetBlendState(
		m_pBlendState.Get(),
		NULL,
		m_StencilMask
	);

	/*! �`�� */
	Direct3D11::GetInstance().GetDeviceContext()->Draw(
		4,		/*!< ���_��(�|���S���Ȃ̂Œ��_����4��) */
		NULL
	);


	return S_OK;
}

/*!
	@fn			�^�C�����O�`��
	@brief		�e�N�X�`�����^�C�����O���ĕ`��
	@detail		���_����UV��͈͊O�ɂ��邱�ƂŎ���
				�`��T�C�Y�̓e�N�X�`���̃T�C�Y�Ɉˑ�����
	@param[in]	�`�悷��e�N�X�`��
	@param[in]	�^�C���\�����銄��
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Sprite::RenderTile(Texture * pTexture, const DirectX::XMFLOAT2 ratio)
{
	HRESULT hr;

	const auto size = pTexture->GetSize();

	/*! ���_���� */
	hr = CreateTilingVertex(size, ratio);
	if (FAILED(hr)) {
		std::string error = "Create tile vertex is failed!";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! �e�N�X�`���̃T�C�Y���L���b�V�����Ă��� */
	m_Size = size;

	/*! �g�|���W�[�Z�b�g */
	Direct3D11::GetInstance().GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
	);

	auto shaderData = ShaderManager::GetInstance().GetShaderData(ShaderManager::c_szTextureAtlasShader);

	/*! ���_�C���v�b�g���C�A�E�g�Z�b�g */
	Direct3D11::GetInstance().GetDeviceContext()->IASetInputLayout(
		shaderData->m_pVertexLayout.Get()
	);

	/*! �V�F�[�_�[�̓o�^ */
	Direct3D11::GetInstance().GetDeviceContext()->VSSetShader(
		shaderData->m_pVertexShader.Get(),
		NULL,
		NULL
	);
	Direct3D11::GetInstance().GetDeviceContext()->PSSetShader(
		shaderData->m_pPixelShader.Get(),
		NULL,
		NULL
	);

	/*! �R���X�^���g�o�b�t�@�̓o�^ */
	Direct3D11::GetInstance().GetDeviceContext()->VSSetConstantBuffers(
		0,
		1,
		shaderData->m_pConstantBuffer.GetAddressOf()
	);
	Direct3D11::GetInstance().GetDeviceContext()->PSSetConstantBuffers(
		0,
		1,
		shaderData->m_pConstantBuffer.GetAddressOf()
	);

	/*! �T���v���[�擾 */
	auto ppSampler = pTexture->GetSamplerState();

	/*! SRV�擾 */
	auto ppSRV = pTexture->GetShaderResourceView();

	/*! �e�N�X�`�� */
	Direct3D11::GetInstance().GetDeviceContext()->PSSetSamplers(
		0,
		1,
		ppSampler
	);
	Direct3D11::GetInstance().GetDeviceContext()->PSSetShaderResources(
		0,
		1,
		ppSRV
	);

	/*! ���W�ϊ� */
	DirectX::XMMATRIX mWorld, mTran, mRot, mScale;
	mWorld = DirectX::XMMatrixIdentity();
	mTran = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	mRot = DirectX::XMMatrixRotationRollPitchYaw(m_Rot.x, m_Rot.y, m_Rot.z);
	mScale = DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, c_ScaleZ);

	/*! ���[���h�ϊ� */
	mWorld = mScale * mRot * mTran;

	/*! �V�F�[�_�[���ɓn���R���X�^���g�o�b�t�@�錾 */
	SpriteShaderBuffer cb;
	SecureZeroMemory(&cb, sizeof(cb));

	/*! �R���X�^���g�o�b�t�@�̃f�[�^�������� */
	auto camera = &Camera::GetInstance();
	const Color& color = pTexture->m_Color;
	DirectX::XMMATRIX m = mWorld * camera->GetViewMatrix()*camera->GetProjMatrix();

	cb.m_WVP = m;					/*!< ���[���h�s�� */
	cb.m_DivNum = { 1,1 };
	cb.m_Index = { 0,0 };
	cb.m_Color = color.GetRGBA();

	/*! UpdateSubResource */
	Direct3D11::GetInstance().GetDeviceContext()->UpdateSubresource(
		shaderData->m_pConstantBuffer.Get(),
		NULL,
		nullptr,
		&cb,
		NULL,
		NULL
	);

	/*! ���_�o�b�t�@�Z�b�g */
	uint32_t stride = sizeof(SpriteVertex);
	uint32_t offset = 0;
	Direct3D11::GetInstance().GetDeviceContext()->IASetVertexBuffers(
		0,
		1,
		m_pVertexBuffer.GetAddressOf(),
		&stride,
		&offset
	);

	/*! �u�����h�X�e�[�g�̐ݒ� */
	Direct3D11::GetInstance().GetDeviceContext()->OMSetBlendState(
		m_pBlendState.Get(),
		NULL,
		m_StencilMask
	);

	/*! �`�� */
	Direct3D11::GetInstance().GetDeviceContext()->Draw(
		4,		/*!< ���_��(�|���S���Ȃ̂Œ��_����4��) */
		NULL
	);

	return S_OK;
}

/*!
	@fn			���_����
	@brief		�X�v���C�g�̒��_�𐶐�����
	@detail		���_�\���̂��g���āA���𒸓_�o�b�t�@�Ƀo�C���h
	@param[in]	�摜�T�C�Y
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT Sprite::CreateVertex(DirectX::XMINT2 size)
{
	/*! ���_�錾 */
	DirectX::XMFLOAT2 leftTop, rightBottom;			/*!< ���_���W */
	DirectX::XMFLOAT2 uvLeftTop, uvRightBottom;		/*!< UV���W */

	/*! �e���_��` */
	leftTop.x		= -0.5f*size.x / c_NormalizeSize;/*!< �� */
	rightBottom.x	=  0.5f*size.x / c_NormalizeSize;/*!< �E */
	leftTop.y		=  0.5f*size.y / c_NormalizeSize;/*!< �� */
	rightBottom.y	= -0.5f*size.y / c_NormalizeSize;/*!< �� */

	/*! UV��` */
	uvLeftTop.x = uvLeftTop.y = 0;
	uvRightBottom.x = uvRightBottom.y = 1;

	/*! ���_�\���̒�` */
	SpriteVertex vertices[] = {
		/*! �E�� */
		{
			/*! ���_ */
			DirectX::XMFLOAT3(
				rightBottom.x,
				leftTop.y,
				c_VertexZ
			),
		/*! UV���W */
		DirectX::XMFLOAT2(
			uvRightBottom.x,
			uvLeftTop.y
		),
	},
		/*! �E�� */
		{
		/*! ���_ */
		DirectX::XMFLOAT3(
			rightBottom.x,
			rightBottom.y,
			c_VertexZ
		),
		/*! UV���W */
		DirectX::XMFLOAT2(
			uvRightBottom.x,
			uvRightBottom.y
		),
	},
		/*! ���� */
		{
		/*! ���_ */
		DirectX::XMFLOAT3(
			leftTop.x,
			leftTop.y,
			c_VertexZ
		),
		/*! UV���W */
		DirectX::XMFLOAT2(
			uvLeftTop.x,
			uvLeftTop.y
		),
	},
		/*! ���� */
		{
		/*! ���_ */
		DirectX::XMFLOAT3(
			leftTop.x,
			rightBottom.y,
			c_VertexZ
		),
		/*! UV���W */
		DirectX::XMFLOAT2(
			uvLeftTop.x,
			uvRightBottom.y
		),
	}
	};

	/*! �|���S��(�l�p�`�|���S��)�̃o�b�t�@���` */
	D3D11_BUFFER_DESC bd;
	SecureZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;				/*!< GPU����ǂݍ��݂Ə������݂����� */
	bd.ByteWidth = sizeof(vertices);			/*!< �o�b�t�@�̃T�C�Y */
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	/*!< ���_�o�b�t�@�Ƃ��ă����_�����O�p�C�v���C���Ƀo�C���h */

	/*! �T�u���\�[�X�̃f�[�^���` */
	D3D11_SUBRESOURCE_DATA subResourceData;
	SecureZeroMemory(&subResourceData, sizeof(subResourceData));
	subResourceData.pSysMem = vertices;			/*!< �������f�[�^�ւ̃|�C���^ */

	/*! ���_�o�b�t�@�̊J�� */
	m_pVertexBuffer.Reset();

	HRESULT hr;

	/*! ���_�o�b�t�@���� */
	hr = Direct3D11::GetInstance().GetDevice()->CreateBuffer(
		&bd,
		&subResourceData,
		m_pVertexBuffer.GetAddressOf()
	);
	if (FAILED(hr)) {
		std::string error = "SpriteBuffer is not Create!";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! ���_�o�b�t�@�Z�b�g */
	uint32_t stride = sizeof(SpriteVertex);
	uint32_t offset = 0;
	Direct3D11::GetInstance().GetDeviceContext()->IASetVertexBuffers(
		0,
		1,
		m_pVertexBuffer.GetAddressOf(),
		&stride,
		&offset
	);

	return S_OK;
}

/*!
	@fn			�^�C�����O�e�N�X�`���̒��_����
	@brief		�^�C�����O�p�̒��_����
	@detail		�^�C�����O�p��UV���g���������_�𐶐�����
	@param[in]	�摜�T�C�Y
	@param[in]	�^�C�����O���銄��
	@return		����:S_OK ���s:E_FAIL
*/
HRESULT API::Sprite::CreateTilingVertex(DirectX::XMINT2 size, DirectX::XMFLOAT2 ratio)
{
	/*! ���_�錾 */
	DirectX::XMFLOAT2 leftTop, rightBottom;			/*!< ���_���W */
	DirectX::XMFLOAT2 uvLeftTop, uvRightBottom;		/*!< UV���W */


#ifdef DEBUG_SPRITE
	/*! �^�C�����O���� */
	if (ratio.x == 1 && ratio.y == 1) {
		std::string error = "�^�C�����O����K�v������܂���B";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! �s���Ȓl */
	if (ratio.x <= 0 || ratio.y <= 0) {
		std::string error = "ratio is invalid value!";
		ErrorLog(error);
		return E_FAIL;
	}

#endif // DEBUG_SPRITE


	/*! UV��` */
	uvLeftTop.x = uvLeftTop.y = 0;
	uvRightBottom.x = ratio.x;
	uvRightBottom.y = ratio.y;

	/*! �e���_��` */
	leftTop.x		= -0.5f*size.x / c_NormalizeSize * ratio.x;/*!< �� */
	rightBottom.x	=  0.5f*size.x / c_NormalizeSize * ratio.x;/*!< �E */
	leftTop.y		=  0.5f*size.y / c_NormalizeSize * ratio.y;/*!< �� */
	rightBottom.y	= -0.5f*size.y / c_NormalizeSize * ratio.y;/*!< �� */

	/*! ���_�\���̒�` */
	SpriteVertex vertices[] = {
		/*! �E�� */
		{
			/*! ���_ */
			DirectX::XMFLOAT3(
				rightBottom.x,
				leftTop.y,
				c_VertexZ
			),
		/*! UV���W */
		DirectX::XMFLOAT2(
			uvRightBottom.x,
			uvLeftTop.y
		),
	},
		/*! �E�� */
		{
			/*! ���_ */
			DirectX::XMFLOAT3(
				rightBottom.x,
				rightBottom.y,
				c_VertexZ
			),
		/*! UV���W */
		DirectX::XMFLOAT2(
			uvRightBottom.x,
			uvRightBottom.y
		),
	},
		/*! ���� */
		{
			/*! ���_ */
			DirectX::XMFLOAT3(
				leftTop.x,
				leftTop.y,
				c_VertexZ
			),
		/*! UV���W */
		DirectX::XMFLOAT2(
			uvLeftTop.x,
			uvLeftTop.y
		),
	},
		/*! ���� */
		{
			/*! ���_ */
			DirectX::XMFLOAT3(
				leftTop.x,
				rightBottom.y,
				c_VertexZ
			),
		/*! UV���W */
		DirectX::XMFLOAT2(
			uvLeftTop.x,
			uvRightBottom.y
		),
	}
	};

	/*! �|���S��(�l�p�`�|���S��)�̃o�b�t�@���` */
	D3D11_BUFFER_DESC bd;
	SecureZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;				/*!< GPU����ǂݍ��݂Ə������݂����� */
	bd.ByteWidth = sizeof(vertices);			/*!< �o�b�t�@�̃T�C�Y */
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	/*!< ���_�o�b�t�@�Ƃ��ă����_�����O�p�C�v���C���Ƀo�C���h */

	/*! �T�u���\�[�X�̃f�[�^���` */
	D3D11_SUBRESOURCE_DATA subResourceData;
	SecureZeroMemory(&subResourceData, sizeof(subResourceData));
	subResourceData.pSysMem = vertices;			/*!< �������f�[�^�ւ̃|�C���^ */

	/*! ���_�o�b�t�@�̊J�� */
	m_pVertexBuffer.Reset();

	HRESULT hr;

	/*! ���_�o�b�t�@���� */
	hr = Direct3D11::GetInstance().GetDevice()->CreateBuffer(
		&bd,
		&subResourceData,
		m_pVertexBuffer.GetAddressOf()
	);
	if (FAILED(hr)) {
		std::string error = "SpriteBuffer is not Create!";
		ErrorLog(error);
		return E_FAIL;
	}
	return S_OK;
}


/*!
	@brief	���W�̃Z�b�^�[
*/
void Sprite::SetPos(DirectX::XMFLOAT3 pos)
{
#ifdef DEBUG_SPRITE
	/*! �N���b�v�����̃I�t�Z�b�g(float�^�̊ۂߌ덷�΍�) */
	const float offset = 0.1f;

	/*! �N���b�v����(z)���`��͈͊O�Ȃ�x�� */
	float nearClip = Camera::GetInstance().GetEyePt().z + Camera::c_NearClip - offset;
	float farClip = Camera::GetInstance().GetEyePt().z + Camera::c_FarClip - offset;

	try
	{
		std::string error = "�X�v���C�g�̓J�����̃N���b�v�̕`��͈͊O�̂��ߕ`�悳��܂���B\n";
		if (pos.z < nearClip) {

			error += "\nNearClip > Pos.z\n";
			error += std::to_string(nearClip + offset) + " > " + std::to_string(pos.z);
			error += "\n\n�X�v���C�g�̓J��������O�ɂ���܂�";
			throw error;
		}
		if (pos.z >= farClip) {

			error += "\nFarClip <= Pos.z\n";
			error += std::to_string(farClip - offset) + " <= " + std::to_string(pos.z);
			error += "\n\n�X�v���C�g�̓J�����̕`��͈͂�艜�ɂ���܂�";
			throw error;
		}
	}
	catch (std::string error)
	{
		ErrorLog(error);
		int ret = 0;
		if (ret == IDOK) {
			exit(NULL);
		}
	}

	
#endif // DEBUG_SPRITE
	m_Pos = pos;
}

/*!
	@brief	���W�̃Z�b�^�[
	@detail	�I�[�o�[���[�h
*/
void Sprite::SetPos(DirectX::XMFLOAT2 pos)
{
	m_Pos = { pos.x,pos.y,m_Pos.z };
}

/*!
	@brief	�X�P�[���̃Z�b�^�[
*/
void API::Sprite::SetScale(DirectX::XMFLOAT2 scale)
{
	m_Scale = { scale.x,scale.y,c_ScaleZ };
}

