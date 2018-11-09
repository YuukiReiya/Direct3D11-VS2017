/*
	@file	ISceneBase.h
	@date	2018/02/22
	@author	番場 宥輝
	@brief	シーンのインターフェース
*/
#pragma once

__interface ISceneBase
{
	void Initialize();
	void Finalize();
	ISceneBase* Update(ISceneBase* scene);
	void Render();
};