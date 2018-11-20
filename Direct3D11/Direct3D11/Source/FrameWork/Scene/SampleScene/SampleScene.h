/*
	@file	SampleScene.h
	@date	2018/11/06
	@author	番場 宥輝
	@brief	サンプルシーン
*/
#pragma once
#include <memory>
#include "../Scene.h"
#include "../../API/Renderer/Sprite/Sprite.h"
#include "../../API/Renderer/Texture/Texture.h"
#include "../../API/Sound/Wav/Wav.h"

class SampleScene final
	: public Scene
{
public:
	SampleScene();
	~SampleScene();

	void Initialize()override;
	void Finalize()override;
	Scene* Update(SceneRoot* root)override;
	void Render()override;

private:
	std::unique_ptr<API::Texture>m_pTex;
	std::unique_ptr<API::Sprite>m_pSprite;
	std::unique_ptr<API::Texture>m_pTex2;
	std::unique_ptr<API::Sprite>m_pSprite2;
	std::unique_ptr<API::Wav>m_pWav;
	std::unique_ptr<API::Wav>m_pWav2;
};

