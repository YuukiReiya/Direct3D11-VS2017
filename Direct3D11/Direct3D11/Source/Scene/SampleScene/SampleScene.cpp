#include "SampleScene.h"

using namespace std;

SampleScene::SampleScene()
{
}


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

	//m_pTex->Load("image.jpg", { 308 ,163});
	//m_pTex2->Load("Smoke.png", { 256,256 });
	//m_pSprite->Initialize();
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
	//m_pSprite->Render(m_pTex.get());
	//m_pSprite2->Render(m_pTex2.get());
}
