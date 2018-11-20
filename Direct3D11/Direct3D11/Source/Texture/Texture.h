/*
	@file	Texture.h
	@date	2018/04/28
	@author	�ԏ� �G�P
	@brief	�e�N�X�`��
*/
#pragma once
#include <D3D11.h>
#include <string>
#include <DirectXMath.h>
#include <wrl/client.h>
#include "../API/ApplicationProgrammingInterface.h"

/*! API�̖��O��ԂɊ܂߂� */
namespace API {

	class Texture
		: public IAPI
	{
	public:
		explicit Texture();
		~Texture();

		/*! �^�C�����O���[�h(�A�h���b�V���O���[�h) */
		enum TileMode {
			/*! �J��Ԃ����� */
			Clamp = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP,			/*!< �f�t�H���g */
			Border = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER,			/*!< SAMPLER_DESC�܂���HLSL�Ŏw�肵�����E�F��ݒ� */
			MirrorOnce = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR_ONCE,
			/*! �^�C�����O */
			Wrap = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP,				/*!< �J��Ԃ� */
			Mirror = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR,			/*!< �J��Ԃ����] */
		};

		/*! �t�B���^�����O���[�h */
		enum FilteringMode {
			Point = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT,			/*!< �|�C���g�t�B���^�����O:�ň��i���ŃR�X�p�� */
			Bilinear = D3D11_FILTER::D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,	/*!< �o�C���j�A�e�N�X�`���t�B���^�����O */
			Trilinear = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR,		/*!< �g�����j�A�e�N�X�`���t�B���^�����O:�f�t�H���g�ݒ� */
			Anisotropic = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC				/*!< �ٕ����t�B���^�����O:�ō��i���ŃR�X�p�� */
		};

		HRESULT IAPI::Initialize();
		HRESULT Initialize(TileMode tileMode);
		HRESULT Initialize(FilteringMode filteringMode);
		HRESULT Initialize(TileMode tileMode, FilteringMode filteringMode);
		HRESULT Initialize(std::string filePath, DirectX::XMINT2 size);
		HRESULT Load(std::string filePath, DirectX::XMINT2 size);
		void IAPI::Finalize();

		/*! �Z�b�^�[ */
		void SetSize(DirectX::XMINT2 size) { m_Size = size; }
		HRESULT SetTileAndFiltering(TileMode tile, FilteringMode filter);

		/*! �Q�b�^�[ */
		ID3D11SamplerState** GetSamplerState() { return m_pSamplerState.GetAddressOf(); }
		ID3D11ShaderResourceView** GetTexture() { return m_pResorceTexture.GetAddressOf(); }
		DirectX::XMINT2 GetSize()const { return m_Size; }
		TileMode GetTileMode()const { return m_eTileMode; }
		FilteringMode GetFilterMode()const { return m_eFilteringMode; }
	private:

		TileMode m_eTileMode;
		FilteringMode m_eFilteringMode;
		DirectX::XMINT2 m_Size;
		//ID3D11Buffer* m_pVertexBuffer;
		/*ID3D11SamplerState* m_pSamplerState;
		ID3D11ShaderResourceView* m_pResorceTexture;*/
		Microsoft::WRL::ComPtr<ID3D11SamplerState>m_pSamplerState;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>m_pResorceTexture;
	};
};