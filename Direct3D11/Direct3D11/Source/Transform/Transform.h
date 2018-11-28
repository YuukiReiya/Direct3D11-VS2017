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
	//DirectX::XMMATRIX m_WorldMatrix;
	//DirectX::XMMATRIX m_ProjMatrix;
	//DirectX::XMMATRIX m_ViewMatrix;

private:
	/*! ���[�J���̍s�� */
	DirectX::XMFLOAT4X4 m_LocalMatrix;
public:
	void SetPos(const DirectX::XMFLOAT3 pos) {
		m_LocalMatrix._41 = pos.x;
		m_LocalMatrix._42 = pos.y;
		m_LocalMatrix._43 = pos.z;
	}

	DirectX::XMFLOAT3 GetEuler()const {

	}

	/*! �ÓI�֐� */

	DirectX::XMMATRIX GetLocalMat()const {
		return DirectX::XMLoadFloat4x4(&m_LocalMatrix);
	}

	DirectX::XMFLOAT3 GetPos()const;
	static inline const DirectX::XMFLOAT3 GetPos(const DirectX::XMMATRIX mat) {
		DirectX::XMFLOAT4X4  tmp;
		DirectX::XMStoreFloat4x4(&tmp, mat);
		float x, y, z;
		x = tmp._41;
		y = tmp._42;
		z = tmp._43;
		return DirectX::XMFLOAT3(x, y, z);
	}

};