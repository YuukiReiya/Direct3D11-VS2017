/*
	@file	Color.h
	@date	2018/11/26
	@author	�ԏ� �G�P
	@brief	�J���[�N���X
*/
#pragma once
#include <DirectXMath.h>

/*!
	@brief	�J���[�N���X
*/
class Color
{
public:
	/*!
		@brief	�R���X�g���N�^
	*/
	Color();

	/*!
		@brief		�����t���R���X�g���N�^
		@param[in]	�ꎞ�ϐ�
	*/
	Color(Color&&color);

	/*!
		@brief		�����t���R���X�g���N�^
		@param[in]	R( 0.0f �` 1.0f )
		@param[in]	G( 0.0f �` 1.0f )
		@param[in]	B( 0.0f �` 1.0f )
		@param[in]	A( 0.0f �` 1.0f )
	*/
	Color(float r, float g, float b, float a = 1.0f);

	/*!
		@brief		�����t���R���X�g���N�^
		@param[in]	FLOAT4�^����J���[�^�֕ϊ�
	*/
	Color(DirectX::XMFLOAT4 color);

	/*!
		@brief	�f�X�g���N�^
		@detail	��f�X�g���N�^
	*/
	~Color();

	/*!
		@def	�ϐ��̕ʖ���`�}�N��
		@detail	�Q�l:https://qiita.com/tyanmahou/items/7fbc5c0638ef9fd4c467
	*/
	#pragma region def
#define PropertyAlias(base,name,...)\
__declspec(property(get = Get_##base, put = Set_##base)) __VA_ARGS__ name;\
__VA_ARGS__ & Get_##base(){return base;}\
void Set_##base(const __VA_ARGS__& value){base = value;}
	#pragma endregion

	/*!
		@fn		�J���[�̃Q�b�^�[
		@brief	�J���[��XMFLOAT3�^�Ŏ擾
		@detail	�J���[��RGB��������XMFLOAT3�^���擾����
	*/
	DirectX::XMFLOAT3 GetRGB()const;

	/*!
		@fn		�J���[�̃Q�b�^�[
		@brief	�J���[��XMFLOAT4�^�Ŏ擾
		@detail	�J���[��RGBA��������XMFLOAT4�^���擾����
	*/
	DirectX::XMFLOAT4 GetRGBA()const;

	float x, y, z, w;

	PropertyAlias(x, r, float);
	PropertyAlias(y, g, float);
	PropertyAlias(z, b, float);
	PropertyAlias(w, a, float);

};


