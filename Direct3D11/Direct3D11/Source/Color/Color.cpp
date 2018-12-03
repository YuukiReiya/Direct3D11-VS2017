/*
	@file	Color.cpp
	@date	2018/11/26
	@author	�ԏ� �G�P
	@brief	�J���[�N���X
*/
#include "Color.h"

/*!
	@brief	�R���X�g���N�^
	@detail	�f�t�H���g�l�𔒂ɂ���
*/
Color::Color() :x(1.0f), y(1.0f), z(1.0f), w(1.0f)
{
}

/*!
	@brief	�����t���R���X�g���N�^
	@param[in]	�ꎞ�ϐ�
*/
Color::Color(Color && color) :x(color.x), y(color.y), z(color.z), w(color.w)
{
}

/*!
	@brief		�����t���R���X�g���N�^
	@param[in]	R( 0.0f �` 1.0f )
	@param[in]	G( 0.0f �` 1.0f )
	@param[in]	B( 0.0f �` 1.0f )
	@param[in]	A( 0.0f �` 1.0f )
*/
Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

/*!
	@brief		�����t���R���X�g���N�^
	@param[in]	FLOAT4�^����J���[�^�֕ϊ�
*/
Color::Color(DirectX::XMFLOAT4 color)
{
	r = color.x;
	g = color.y;
	b = color.z;
	a = color.w;
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
