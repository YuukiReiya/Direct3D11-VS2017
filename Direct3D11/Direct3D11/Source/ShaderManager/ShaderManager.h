/*
	@file	ShaderManager.h
	@date	2018/03/04
	@author	�ԏ� �G�P
	@brief	�V�F�[�_�[�֘A
	@detail	vector,map�̒���:http://msty.hatenablog.jp/entry/2016/08/18/144934
*/
#pragma once
#include <D3D11.h>
#include <unordered_map>
#include <wrl/client.h>
#include "../Singleton/Singleton.h"

#if defined DEBUG||_DEBUG
# define DEBUG_SHADER
#endif

/*! Direct3D11�֘A */
namespace D3D11 {

	/*! �`��֘A�̖��O��ԂɊ܂߂� */
	namespace Graphic {

		/*!
			@brief	�V�F�[�_�[���\������\����
		*/
		struct ShaderData
		{
		public:
			/*!
				@brief	�R���X�g���N�^
			*/
			ShaderData(){
				SecureZeroMemory(this, sizeof(this));
				m_pVertexLayout		= nullptr;
				m_pVertexShader		= nullptr;
				m_pPixelShader		= nullptr;
				m_pConstantBuffer	= nullptr;
			}
			/*!
				@brief	�f�X�g���N�^
			*/
			~ShaderData()
			{
				m_pVertexLayout.Reset();
				m_pVertexShader.Reset();
				m_pPixelShader.Reset();
				m_pConstantBuffer.Reset();
			};

			Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_pVertexLayout;	/*< �C���v�b�g���C�A�E�g */
			Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_pVertexShader;	/*< ���_�V�F�[�_�[ */
			Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pPixelShader;		/*< �s�N�Z���V�F�[�_�[ */
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_pConstantBuffer;	/*< �R���X�^���g�o�b�t�@�[ */
		};

		/*!
			@brief	�V�F�[�_�[�Ǘ��N���X
			@detail	�V�F�[�_�[���쐬�����Ƃ��`��o����f�t�H���g�V�F�[�_�[��p�ӂ���
		*/
		class ShaderManager
			:public Singleton<ShaderManager>
		{
		public:
			~ShaderManager();

			static const std::string c_SpriteDefault;
			static const std::string c_MeshDefault;

			HRESULT AddNewShaderData(std::string szKeyName, ShaderData* pNewShaderData);	/*!< �\���̂����X�g�ɒǉ��o�^ */
			HRESULT Initialize();
			void Finalize();
			HRESULT MakeShader(std::string szFileName, std::string szFuncName, std::string szProfileName, void** ppShader, ID3DBlob** ppBlob);
			ShaderData* GetShaderData(std::string szKeyName);

		private:
			ShaderManager();
			friend class Singleton<ShaderManager>;

			ShaderData* m_pAddDataRef;/*!< �f�[�^�ǉ��p�̎Q�ƃ����o */
			std::unordered_map<std::string, ShaderData*>m_pShaderDataUMap;


		};

	}
}
