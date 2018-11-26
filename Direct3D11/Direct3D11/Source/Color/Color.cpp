/*
	@file	Color.cpp
	@date	2018/11/26
	@author	�ԏ� �G�P
	@brief	�J���[�N���X
*/
#include "Color.h"

/*!
	@brief	�R���X�g���N�^
	@detail	��R���X�g���N�^
*/
Color::Color()
{
}

/*!
	@brief	�f�X�g���N�^
	@detail	��f�X�g���N�^
*/
Color::~Color()
{
}

/*!
	@fn		�J���[�̃Q�b�^�[
	@brief	�J���[��XMFLOAT3�^�Ŏ擾
	@detail	�J���[��RGB��������XMFLOAT3�^���擾����
*/
DirectX::XMFLOAT3 Color::GetRGB() const
{
	return DirectX::XMFLOAT3(x, y, z);
}

/*!
	@fn		�J���[�̃Q�b�^�[
	@brief	�J���[��XMFLOAT4�^�Ŏ擾
	@detail	�J���[��RGBA��������XMFLOAT4�^���擾����
*/
DirectX::XMFLOAT4 Color::GetRGBA() const
{
	return DirectX::XMFLOAT4(x, y, z, w);
}
