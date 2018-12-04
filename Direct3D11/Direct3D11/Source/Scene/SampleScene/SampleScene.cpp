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
	m_pSprite2 = make_unique<Sprite>();
	m_pTex2 = make_unique<Texture>();
	m_pSprite3 = make_unique<Sprite>();

	m_pSprite = make_unique<Sprite>();
	m_pSprite->Initialize();
	m_pSprite2->Initialize();
	m_pSprite3->Initialize();
	//m_pTex->Initialize("image.jpg", { 308,163 },API::ITexture::Wrap);
	//m_pTex->Initialize("test.png", { 308,163 }, API::ITexture::Wrap);
	m_pTex->Initialize("red.png", { 800,600 });
	m_pTex2->Initialize("blue.png", { 800,600 });



	m_pWav = make_unique<Wave>();
	////m_pWav->Load("07 フォーチュンナンバー0405.wav");
	//m_pWav->Play(true);
	//m_pWav->SetVolume(0);
	//m_pWav2 = make_unique<Wave>();
	//m_pWav2->Load("Resource/Sound/se.wav");
	//m_pWav2->Play(true);


	m_pTexA = make_unique<TextureAtlas>();
	m_pTexA->Initialize("at.png", { 3,4 },API::ITexture::Wrap);
	

	//m_pTexA->SetSize({ 100,100 });
	m_pTexA->SetAtlasIndex({ 0,0 });
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
using namespace Keyboard;
Scene * SampleScene::Update(SceneRoot * root)
{
	Keyboard::Update();

	auto pos = m_pSprite.get()->GetPos();
	auto tmp = pos;
	pos.x -= Keyboard::GetButton('A') ? 0.1f : 0;
	pos.x += Keyboard::GetButton('D') ? 0.1f : 0;

	pos.z += Keyboard::GetButton('W') ? 0.1f : 0;
	pos.z -= Keyboard::GetButton('S') ? 0.1f : 0;

	static	DirectX::XMFLOAT2 scale = { 1,1 };
	scale.x+= Keyboard::GetButton('Z') ? 0.1f : 0;
	scale.x -= Keyboard::GetButton('C') ? 0.1f : 0;

	//static DirectX::XMFLOAT3 angle = { 0,0,0 };
	//angle.x+= Keyboard::GetButton('N') ? 0.1f : 0;
	//angle.x -= Keyboard::GetButton('M') ? 0.1f : 0;

	m_pSprite.get()->SetPos(pos);
	m_pSprite.get()->SetScale(scale);
	//m_pSprite.get()->SetRot(angle);

	auto& cr = m_pTexA->m_Color;

	if (GetButton('R')) {
		cr.x += 0.01f;
	}
	else if (GetButton('T')) {
		cr.x -= 0.01f;
	}

	if (GetButton('G')) {
		cr.y += 0.01f;
	}
	else if (GetButton('H')) {
		cr.y -= 0.01f;
	}

	if (GetButton('B')) {
		cr.z += 0.01f;
	}
	else if (GetButton('N')) {
		cr.z -= 0.01f;
	}

	if (GetButton('K')) {
		cr.w += 0.01f;
	}
	else if (GetButton('L')) {
		cr.w -= 0.01f;
	}

	if (GetButtonDown('O')) {
		std::cout << cr.x << "," << cr.y << "," << cr.z << "," << cr.w << "\n";
		std::cout << cr.r << "," << cr.g << "," << cr.b << "," << cr.a << "\n";
	}

	//m_pSprite.get()->m_Color = cr;


	if (Keyboard::GetButtonDown(Keyboard::LEFT)) {
		printf("aaka");
		m_pWav->Pause();
	}
	else if (Keyboard::GetButtonDown(Keyboard::UP)) {
		m_pWav->Play();
	}
	else if (Keyboard::GetButtonDown(Keyboard::RIGHT)) {
		m_pWav->Stop();
	}


	return this;
}

/*!
	@brief	描画
*/
void SampleScene::Render()
{
	//m_pSprite2->Render(m_pTex2.get());
	//m_pSprite->SetPos({ 1,0 });
	//m_pSprite->SetPos({0,0,0});
	/*m_pSprite->SetPos({ 1,0 });
	m_pSprite->Render(m_pTex.get());*/

	//m_pSprite2->Render(m_pTexA.get());
	//m_pSprite2->SetPos({ 0,0,-0.1 });
	m_pSprite3->Render(m_pTexA.get());
	m_pSprite->Render(m_pTex.get());
	m_pSprite2->Render(m_pTex2.get());
}
