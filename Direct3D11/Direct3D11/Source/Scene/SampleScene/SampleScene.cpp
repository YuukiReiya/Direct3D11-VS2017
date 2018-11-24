/*
	@file	SampleScene.cpp
	@date	2018/11/06
	@author	番場 宥輝
	@brief	サンプルシーン
*/
#include "SampleScene.h"
#include "../../ShaderManager/ShaderManager.h"
#include "../../Input/Keyboard/Keyboard.h"


/*!
	@brief	名前空間
	@detail	usingディレクティブ
*/
using namespace std;
using namespace D3D11;
using namespace API;

/*!
	@brief	コンストラクタ
*/
SampleScene::SampleScene()
{
}

/*!
	@brief	デストラクタ
*/
SampleScene::~SampleScene()
{
	Finalize();
}

/*!
	@brief	初期化
*/
void SampleScene::Initialize()
{
	m_pTex = make_unique<Texture>();
	//m_pSprite = make_unique<Sprite>();
	//m_pTex2 = make_unique<Texture>();
	//m_pSprite2 = make_unique<Sprite>();

	m_pSprite = make_unique<Sprite>();

	m_pTex->Initialize("image.jpg", { 308,163 });
	////m_pSprite->Initialize();
	//m_pTex2->Initialize("test.png", { 256,256 });
	//m_pSprite2->Initialize();

	//m_pWav = make_unique<Wave>();
	//m_pWav->Load("07 フォーチュンナンバー0405.wav");
	//m_pWav->Play(true);
	//m_pWav2 = make_unique<Wave>();
	//m_pWav2->Load("Resource/Sound/se.wav");
	//m_pWav2->Play(true);


	m_pTexA = make_unique<TextureAtlas>();
	m_pTexA->Initialize("image.jpg", { 1,1 });
	//m_pTexA->Initialize()
}

/*!
	@brief	破棄
*/
#include "../../Direct3D11/Direct3D11.h"
void SampleScene::Finalize()
{
}

/*!
	@brief	更新
*/
#include <iostream>
Scene * SampleScene::Update(SceneRoot * root)
{
	//Keyboard::Update();

	//auto pos = m_pSprite.get()->GetPos();
	//auto tmp = pos;
	//pos.x -= Keyboard::GetButton('A') ? 0.1f : 0;
	//pos.x += Keyboard::GetButton('D') ? 0.1f : 0;

	//pos.z += Keyboard::GetButton('W') ? 0.1f : 0;
	//pos.z -= Keyboard::GetButton('S') ? 0.1f : 0;

	//static	DirectX::XMFLOAT2 scale = { 1,1 };
	//scale.x+= Keyboard::GetButton('Z') ? 0.1f : 0;
	//scale.x -= Keyboard::GetButton('C') ? 0.1f : 0;

	//static DirectX::XMFLOAT3 angle = { 0,0,0 };
	//angle.x+= Keyboard::GetButton('N') ? 0.1f : 0;
	//angle.x -= Keyboard::GetButton('M') ? 0.1f : 0;

	//m_pSprite.get()->SetPos(pos);
	//m_pSprite.get()->SetScale(scale);
	//m_pSprite.get()->SetRot(angle);


	//if (Keyboard::GetButtonDown(Keyboard::LEFT)) {
	//	printf("aaka");
	//	m_pWav->Pause();
	//}
	//else if (Keyboard::GetButtonDown(Keyboard::UP)) {
	//	m_pWav->Play();
	//}
	//else if (Keyboard::GetButtonDown(Keyboard::RIGHT)) {
	//	m_pWav->Stop();
	//}


	return this;
}

/*!
	@brief	描画
*/
void SampleScene::Render()
{
	//m_pSprite2->Render(m_pTex2.get());
	//m_pSprite->Render(m_pTex.get());
	m_pSprite->Render(m_pTexA.get());
}
