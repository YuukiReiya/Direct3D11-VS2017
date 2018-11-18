/*
	@file	Texture.h
	@date	2018/04/28
	@author	番場 宥輝
	@brief	テクスチャ
*/
#pragma once
#include <D3D11.h>
#include <string>
#include <DirectXMath.h>
#include <wrl/client.h>
#include "../../FrameWork/API/ApplicationProgrammingInterface.h"

/*! APIの名前空間に含める */
namespace API {

	class Texture
		: public IAPI
	{
	public:
		explicit Texture();
		~Texture();

		/*! タイリングモード(アドレッシングモード) */
		enum TileMode {
			/*! 繰り返し無し */
			Clamp = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP,			/*!< デフォルト */
			Border = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER,			/*!< SAMPLER_DESCまたはHLSLで指定した境界色を設定 */
			MirrorOnce = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR_ONCE,
			/*! タイリング */
			Wrap = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP,				/*!< 繰り返し */
			Mirror = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR,			/*!< 繰り返し反転 */
		};

		/*! フィルタリングモード */
		enum FilteringMode {
			Point = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT,			/*!< ポイントフィルタリング:最悪品質でコスパ良 */
			Bilinear = D3D11_FILTER::D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,	/*!< バイリニアテクスチャフィルタリング */
			Trilinear = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR,		/*!< トリリニアテクスチャフィルタリング:デフォルト設定 */
			Anisotropic = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC				/*!< 異方性フィルタリング:最高品質でコスパ悪 */
		};

		HRESULT IAPI::Initialize();
		HRESULT Initialize(TileMode tileMode);
		HRESULT Initialize(FilteringMode filteringMode);
		HRESULT Initialize(TileMode tileMode, FilteringMode filteringMode);
		HRESULT Initialize(std::string filePath, DirectX::XMINT2 size);
		HRESULT Load(std::string filePath, DirectX::XMINT2 size);

		void IAPI::Finalize();

		/*! セッター */
		void SetSize(DirectX::XMINT2 size) { m_Size = size; }
		HRESULT SetTileAndFiltering(TileMode tile, FilteringMode filter);

		/*! ゲッター */
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
