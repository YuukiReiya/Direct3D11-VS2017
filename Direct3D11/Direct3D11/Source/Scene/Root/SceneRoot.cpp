/*
	@file	SceneRoot.cpp
	@date	2018/02/22
	@author	番場 宥輝
	@brief	シーンの遷移クラス
*/
#include "SceneRoot.h"
#include "../SampleScene/SampleScene.h"


/*!
	@brief	コンストラクタ
*/
SceneRoot::SceneRoot()
	:m_pScene(nullptr)
{
}

/*!
	@brief	デストラクタ
*/
SceneRoot::~SceneRoot()
{
	Finalize();
}

/*!
	@brief	初期化
*/
void SceneRoot::Initialize()
{
	/*! 一番最初のシーン */
	m_pScene = new SampleScene();
	m_pScene->Initialize();
}

/*!
	@brief	更新
	@return	シーンのポインタ
*/
ISceneBase * SceneRoot::Update(ISceneBase * scene)
{
	/*! シーンの実行 */
	ISceneBase*pNext = m_pScene->Update(this);

	/*! 戻り値が現在のシーンと異なっていればシーン遷移 */
	if (pNext != m_pScene) 
	{
		/*! シーンの破棄 */
		m_pScene->Finalize();
		delete m_pScene;

		/*!  */
		Scene* casted = dynamic_cast<Scene*>(pNext);
		m_pScene = casted;
		m_pScene->Initialize();
	}
	return this;
}

/*!
	@brief	描画
*/
void SceneRoot::Render()
{
	m_pScene->Render();
}

/*!
	@brief	破棄
*/
void SceneRoot::Finalize()
{
	delete m_pScene;
	m_pScene = nullptr;
}
