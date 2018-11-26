/*
	@file	Color.cpp
	@date	2018/11/26
	@author	番場 宥輝
	@brief	カラークラス
*/
#include "Color.h"

/*!
	@brief	コンストラクタ
	@detail	空コンストラクタ
*/
Color::Color()
{
}

/*!
	@brief	デストラクタ
	@detail	空デストラクタ
*/
Color::~Color()
{
}

/*!
	@fn		カラーのゲッター
	@brief	カラーをXMFLOAT3型で取得
	@detail	カラーのRGBが入ったXMFLOAT3型を取得する
*/
DirectX::XMFLOAT3 Color::GetRGB() const
{
	return DirectX::XMFLOAT3(x, y, z);
}

/*!
	@fn		カラーのゲッター
	@brief	カラーをXMFLOAT4型で取得
	@detail	カラーのRGBAが入ったXMFLOAT4型を取得する
*/
DirectX::XMFLOAT4 Color::GetRGBA() const
{
	return DirectX::XMFLOAT4(x, y, z, w);
}
