/*
	@file	SampleScene.cpp
	@date	2018/11/06
	@author	�ԏ� �G�P
	@brief	�T���v���V�[��
*/
#include "SampleScene.h"
#include "../../Shader/ShaderManager.h"
#include "../../Input/Keyboard/Keyboard.h"

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
	Keyboard::Update();

	auto pos = m_pSprite.get()->GetPos();

	pos.x -= Keyboard::GetButton('A') ? 0.1f : 0;
	pos.x += Keyboard::GetButton('D') ? 0.1f : 0;

	pos.z += Keyboard::GetButton('W') ? 0.1f : 0;
	pos.z -= Keyboard::GetButton('S') ? 0.1f : 0;

	static	DirectX::XMFLOAT2 scale = { 1,1 };
	scale.x+= Keyboard::GetButton('Z') ? 0.1f : 0;
	scale.x -= Keyboard::GetButton('C') ? 0.1f : 0;

	static DirectX::XMFLOAT3 angle = { 0,0,0 };
	angle.x+= Keyboard::GetButton('N') ? 0.1f : 0;
	angle.x -= Keyboard::GetButton('M') ? 0.1f : 0;

	m_pSprite.get()->SetPos(pos);
	m_pSprite.get()->SetScale(scale);
	m_pSprite.get()->SetRot(angle);
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
