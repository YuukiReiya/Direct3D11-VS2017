/*
	@file	Sprite.h
	@date	2018/03/04
	@author	�ԏ� �G�P
	@brief	�X�v���C�g�֘A
	@detail	���u�����h�ɂ��ĎQ�l�T�C�g:http://neareal.net/index.php?ComputerGraphics%2FXNA%2FBlendState
*/
#pragma once
#include <string>
#include <D3D11.h>
#include "../ShaderBase/StructShaderBase.h"
#include <DirectXMath.h>
#include "../IRenderer/IRenderer.h"
#include "../Texture/Texture.h"
#include "../TextureAtlas/TextureAtlas.h"

/*! API�̖��O��ԂɊ܂߂� */
namespace API{
	/*!
		�X�v���C�g�������N���X
	*/
	class Sprite
		{
		public:

			/*!
				@brief	�R���X�g���N�^
			*/
			explicit Sprite();

			/*!
				@brief	�f�X�g���N�^
			*/
			~Sprite();

			/*!
				@fn		�C�j�V�����C�Y
				@brief	������
				@detail	�u�����h�X�e�[�g�̍쐬���s��
			*/
			HRESULT Initialize();

			/*!
				@fn		�t�@�C�i���C�Y
				@brief	�j������
				@detail	�����o�̖����I�ȉ���ƃ����o�̏�����
			*/
			void Finalize();

			/*!
				@fn		�����[�X
				@brief	�������
				@detail	�����o�̖����I�ȉ��
			*/
			void Release();

			/*!
				@fn			�e�N�X�`���̕`��
				@brief		�V���v���e�N�X�`���̕`��
				@detail		map,unmap���g���ăe�N�X�`���}�b�s���O������`��
				@param[in]	�`�悷��e�N�X�`��
				@return		����:S_OK ���s:E_FAIL
			*/
			HRESULT Render(Texture* pTexture);

			/*!
				@fn			�e�N�X�`���̕`��
				@brief		�A�g���X�e�N�X�`���̕`��
				@detail		SubResource���g����UpdateSubResource������`��
				@param[in]	�`�悷��e�N�X�`��
				@return		����:S_OK ���s:E_FAIL
			*/
			HRESULT Render(TextureAtlas* pTexture);

			/*!
				@fn			�^�C�����O�`��
				@brief		�e�N�X�`�����^�C�����O���ĕ`��
				@detail		���_����UV��͈͊O�ɂ��邱�ƂŎ���
							���䗦�̈ێ���D�悵�Ă��邽�߁A�ʓr�傫����ύX����K�v������
				@param[in]	�`�悷��e�N�X�`��
				@param[in]	�^�C�����銄��
				@return		����:S_OK ���s:E_FAIL
			*/
			HRESULT RenderTile(Texture* pTexture, const DirectX::XMFLOAT2 ratio);


			DirectX::XMFLOAT3 GetPos()const { return m_Pos; }

			void SetPos(DirectX::XMFLOAT3 pos);
			void SetPos(DirectX::XMFLOAT2 pos);
			void SetRot(DirectX::XMFLOAT3 rot) { m_Rot.x = rot.x, m_Rot.y = rot.y, m_Rot.z = rot.z; }
			void SetScale(DirectX::XMFLOAT2 scale);
			void SetAlpha(float alpha) { m_Alpha = alpha; }
			void SetStencilMask(uint32_t mask) { m_StencilMask = mask; }

			/*!
				@fn			�u�����h�X�e�[�g�̍쐬
				@brief		�쐬�����u�����h�X�e�[�g�͕`�掞�Ƀo�C���h�����
				@detail		�����o�̃u�����h�X�e�[�g����ύX
				@param[in]	���Ȓ�`�̃u�����h�X�e�[�g
			*/
			void CreateAlphaBlendState(D3D11_BLEND_DESC desc);

		private:
			/*!
				@var	c_VertexCount
				@brief	�X�v���C�g�̒��_��
				@detail	�X�v���C�g�̒��_���̒萔��
			*/
			static constexpr int c_VertexCount = 4;/*!< �X�v���C�g�̒��_�� */

			/*!
				@var	c_NormalizeSize
				@brief	��ƂȂ�T�C�Y
				@detail	���̃s�N�Z����Scale��1�ɑ�������
				@value	100.0f
			*/
			static const float c_NormalizeSize;

			/*!
				@var	c_ScaleZ
				@brief	�|����Z�X�P�[��
				@detail	�������钸�_��Z�����̑傫��
				@value	0
			*/
			static const float c_ScaleZ;

			/*!
				@var	c_VertexZ
				@brief	�|���̒��_�����ʒu
				@detail	CreateVertex�֐��Ő������钸�_��Z�ʒu
				@value	0
			*/
			static const float c_VertexZ;

			/*!
				@fn			���_����
				@brief		�X�v���C�g�̒��_�𐶐�����
				@detail		���_�\���̂��g���āA���𒸓_�o�b�t�@�Ƀo�C���h
				@param[in]	�摜�T�C�Y
				@return		����:S_OK ���s:E_FAIL
			*/
			HRESULT CreateVertex(DirectX::XMINT2 size);

			/*!
				@fn			�^�C�����O�e�N�X�`���̒��_����
				@brief		�^�C�����O�p�̒��_����
				@detail		�^�C�����O�p��UV���g���������_�𐶐�����
				@param[in]	�摜�T�C�Y
				@param[in]	�^�C�����O���銄��
				@return		����:S_OK ���s:E_FAIL
			*/
			HRESULT CreateTilingVertex(DirectX::XMINT2 size, DirectX::XMFLOAT2 ratio);

			uint32_t									m_StencilMask;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_pVertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11BlendState>	m_pBlendState;

			/****************************************/
			/*		�@�X�v���C�g�̃p�����[�^		*/
			/****************************************/


			/*! ���[�J�����W�n */
			DirectX::XMFLOAT3 m_Pos;
			DirectX::XMFLOAT3 m_Rot;
			DirectX::XMFLOAT3 m_Scale;
		public:
			DirectX::XMFLOAT4 m_Color;
		private:
			/*! �X�v���C�g�� */
			DirectX::XMINT2 m_Size;
			float m_Alpha;

	};

}

/*! Direct3D11�֘A�̖��O��� */
namespace D3D11 {

	/*! �`��֘A�̖��O��ԂɊ܂߂� */
	namespace Graphic {

		/****************************************/
		/*		�X�v���C�g�ň����\����			*/
		/****************************************/

		/*!
			@brief	�X�v���C�g�̒��_�\����
		*/
		struct SpriteVertex
			:public VARTEX_BASE
		{
			SpriteVertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 uv) {
				m_Pos = pos, m_UV = uv;
			}
			DirectX::XMFLOAT2 m_UV;/*< UV���W */
		};

		/*!
			@brief	�X�v���C�g�̃R���X�^���g�o�b�t�@�\����
		*/
		struct SpriteShaderBuffer
			:CONSTANT_BUFFER_BASE
		{
			ALIGN16<DirectX::XMFLOAT2>	m_DivNum;
			ALIGN16<DirectX::XMFLOAT2>	m_Index;
			ALIGN16<DirectX::XMFLOAT4>	m_Color;	/*< �J���[ */
		};
	}
}