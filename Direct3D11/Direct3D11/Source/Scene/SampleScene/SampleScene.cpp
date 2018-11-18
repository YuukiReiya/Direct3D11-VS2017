/*
	@file	SampleScene.cpp
	@date	2018/11/06
	@author	�ԏ� �G�P
	@brief	�T���v���V�[��
*/
#include "SampleScene.h"
#include "../../Shader/ShaderManager.h"
/*!
	@brief	���O���
	@detail	using�f�B���N�e�B�u
*/
using namespace std;
using namespace D3D11;
using namespace API;

/*!
	@brief	�R���X�g���N�^
*/
SampleScene::SampleScene()
{
}

/*!
	@brief	�f�X�g���N�^
*/
SampleScene::~SampleScene()
{
	Finalize();
}

/*!
	@brief	������
*/
void SampleScene::Initialize()
{
	//m_pTex = make_unique<Texture>();
	//m_pSprite = make_unique<Sprite>();
	//m_pTex2 = make_unique<Texture>();
	//m_pSprite2 = make_unique<Sprite>();


	m_pTex = make_unique<Texture>();
	m_pSprite = make_unique<Sprite>();

	m_pTex2 = make_unique<Texture>();
	m_pSprite2 = make_unique<Sprite>();


	m_pTex->Load("image.jpg", { 308,163 });
	m_pSprite->Initialize();
	m_pTex2->Load("test.png", { 256,256 });
	m_pSprite2->Initialize();
}

/*!
	@brief	�j��
*/
void SampleScene::Finalize()
{
	//m_pTex->Finalize();
	//m_pSprite->Release();
}

/*!
	@brief	�X�V
*/
Scene * SampleScene::Update(SceneRoot * root)
{
	return this;
}

/*!
	@brief	�`��
*/
void SampleScene::Render()
{
	m_pSprite->Render(m_pTex2.get());
	m_pSprite->Render(m_pTex.get());
}
