/*
	@file	Transform.h
	@date	2018/11/18
	@author	番場 宥輝
	@brief	トランスフォームクラス
	@detail	Position,Rotation,Scaleの3つと行列を含む
	@detail	αブレンドについて参考サイト:http://neareal.net/index.php?ComputerGraphics%2FXNA%2FBlendState
*/
#pragma once
#include <DirectXMath.h>

class Transform
{
public:
	explicit Transform();
	~Transform();

	/*! 座標系 */
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT4 m_Rot;
	DirectX::XMFLOAT3 m_Scale;

	/*! 行列 */
	DirectX::XMMATRIX m_WorldMatrix;
	DirectX::XMMATRIX m_ProjMatrix;
	DirectX::XMMATRIX m_ViewMatrix;

	/*! 静的関数 */

	/*! ワールド変換後の行列 */
	const inline DirectX::XMMATRIX GetWVP();
	const static inline DirectX::XMMATRIX GetWVP(DirectX::XMMATRIX world, DirectX::XMMATRIX proj, DirectX::XMMATRIX view);
};

