/*
	@file	SampleScene.cpp
	@date	2018/11/06
	@author	番場 宥輝
	@brief	サンプルシーン
*/
#include "SampleScene.h"

/*!
	@brief	名前空間
	@detail	usingディレクティブ
*/
using namespace std;

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
	//m_pTex = make_unique<Texture>();
	//m_pSprite = make_unique<Sprite>();
	//m_pTex2 = make_unique<Texture>();
	//m_pSprite2 = make_unique<Sprite>();

	//m_pTex->Load("image.jpg", { 308 ,163});
	//m_pTex2->Load("Smoke.png", { 256,256 });
	//m_pSprite->Initialize();
}

/*!
	@brief	破棄
*/
void SampleScene::Finalize()
{
	//m_pTex->Finalize();
	//m_pSprite->Release();
}

/*!
	@brief	更新
*/
Scene * SampleScene::Update(SceneRoot * root)
{
	return this;
}

/*!
	@brief	描画
*/
void SampleScene::Render()
{
	//m_pSprite->Render(m_pTex.get());
	//m_pSprite2->Render(m_pTex2.get());
}
