/*
	@file	Transform.h
	@date	2018/11/18
	@author	�ԏ� �G�P
	@brief	�g�����X�t�H�[���N���X
	@detail	Position,Rotation,Scale��3�ƍs����܂�
	@detail	���u�����h�ɂ��ĎQ�l�T�C�g:http://neareal.net/index.php?ComputerGraphics%2FXNA%2FBlendState
*/
#pragma once
#include <DirectXMath.h>

class Transform
{
public:
	explicit Transform();
	~Transform();

	/*! ���W�n */
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT4 m_Rot;
	DirectX::XMFLOAT3 m_Scale;

	/*! �s�� */
	DirectX::XMMATRIX m_WorldMatrix;
	DirectX::XMMATRIX m_ProjMatrix;
	DirectX::XMMATRIX m_ViewMatrix;

	/*! �ÓI�֐� */

	/*! ���[���h�ϊ���̍s�� */
	const inline DirectX::XMMATRIX GetWVP();
	const static inline DirectX::XMMATRIX GetWVP(DirectX::XMMATRIX world, DirectX::XMMATRIX proj, DirectX::XMMATRIX view);
};

