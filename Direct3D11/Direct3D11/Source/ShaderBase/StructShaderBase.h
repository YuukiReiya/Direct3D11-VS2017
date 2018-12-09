/*
	@file	StructShaderBase.h
	@date	2018/03/04
	@author	�ԏ� �G�P
	@brief	�V�F�[�_�[�֘A�̍\���̐錾
*/
#pragma once
#include <DirectXMath.h>


/*! Direct3D11�֘A�̖��O��� */
namespace D3D11 {

	/*! �`��֘A�̖��O��� */
	namespace Graphic {

		/*!
			@brief	��꒸�_�\����
		*/
		struct VARTEX_BASE
		{
			DirectX::XMFLOAT3 m_Pos;/*< ���W */
		};

		/*!
			@brief	�V�F�[�_�[���ɓn���R���X�^���g�o�b�t�@�̊��\����
		*/
#pragma pack(push,16)

		/*!
			@brief	pack�}�N���ɕύX
		*/
		struct CONSTANT_BUFFER_BASE
		{
			/*!
				@brief	�G�C���A�X�e���v���[�g��p�����ʖ���`
			*/
			
			template<typename alignType>
			//using ALIGN16 = __declspec(align(16)) alignType;/*!< 16�o�C�g���E�Ɍ^��ݒ肷�邽�߂̕ʖ� */
			using ALIGN16 = alignType;/*!< 16�o�C�g���E�Ɍ^��ݒ肷�邽�߂̕ʖ� */
			/*! �����o�̍s�� */
			//ALIGN16<DirectX::XMMATRIX>m_WorldMatrix;		/*!< ���[���h */
			//ALIGN16<DirectX::XMMATRIX>m_ProjectionMatrix;	/*!< �ˉe�s�� */
			//ALIGN16<DirectX::XMMATRIX>m_ViewMatrix;			/*!< �r���[�s�� */
			ALIGN16<DirectX::XMMATRIX>m_WVP;
		};
#pragma pack(pop)
	};
};