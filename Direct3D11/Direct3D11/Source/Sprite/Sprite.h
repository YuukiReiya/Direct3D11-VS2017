/*
	@file	Sprite.h
	@date	2018/03/04
	@author	番場 宥輝
	@brief	スプライト関連
	@detail	αブレンドについて参考サイト:http://neareal.net/index.php?ComputerGraphics%2FXNA%2FBlendState
*/
#pragma once
#include <string>
#include <D3D11.h>
#include "../ShaderBase/StructShaderBase.h"
//#include "../Shader/ShaderManager.h"
#include <DirectXMath.h>
#include "../API/ApplicationProgrammingInterface.h"
#include "../IRenderer/IRenderer.h"
#include "../Texture/Texture.h"

#ifdef _DEBUG
#define DEBUG_SPRITE
#endif // _DEBUG

/*! APIの名前空間に含める */
namespace API{
		/*!
			スプライトを扱うクラス
		*/
	class Sprite
		:public API::IAPI
		{
		public:
			explicit Sprite();
			~Sprite();

			/*! 描画モード */
			enum Mode {
				Single,		/*!< ノーマルテクスチャ */
				Multiple	/*!< アトラステクスチャ */
			};

			HRESULT IAPI::Initialize();
			void IAPI::Finalize();
			void Release();
			HRESULT Render(Texture* pTexture, bool isReverse = false);

			DirectX::XMFLOAT3 GetPos()const { return m_Pos; }

			void SetPos(DirectX::XMFLOAT3 pos);
			void SetPos(DirectX::XMFLOAT2 pos);
			void SetRot(DirectX::XMFLOAT3 rot) { m_Rot.x = rot.x, m_Rot.y = rot.y, m_Rot.z = rot.z; }
			void SetScale(DirectX::XMFLOAT2 scale);
			void SetSplitTexture(DirectX::XMINT2 divNum);/*!< テクスチャの分割 */
			void SetActivateIndex(DirectX::XMINT2 index);/*!< 描画に使用するするテクスチャを変更 */
			void SetAlpha(float alpha) { m_Alpha = alpha; }
			void SetStencilMask(uint32_t mask) { m_StencilMask = mask; }

			void CreateAlphaBlendState();

		private:
			static constexpr int c_VertexCount = 4;/*!< スプライトの頂点数 */
			static const float c_NormalizeSize;
			static const float c_ScaleZ;
			static const float c_VertexZ;
			HRESULT CreateVertex(DirectX::XMINT2 size);

			HRESULT CreateClampVertex(DirectX::XMINT2 size);	/*!< 一枚絵タイリング/分割無し */
			HRESULT CreateTilingVertex(DirectX::XMINT2 size);	/*!< タイリング用の頂点生成 */
			HRESULT CreateSplitVertex(DirectX::XMINT2 size);	/*!< 分割用頂点生成 */

			std::string m_szShaderDataUsage;
			uint32_t	m_StencilMask;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_pVertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11BlendState>	m_pBlendState;

			/****************************************/
			/*		　スプライトのパラメータ		*/
			/****************************************/


			/*! ローカル座標系 */
			DirectX::XMFLOAT3 m_Pos;
			DirectX::XMFLOAT3 m_Rot;
			DirectX::XMFLOAT3 m_Scale;
			DirectX::XMFLOAT3 m_Color;

			/*! スプライトの */
			DirectX::XMINT2 m_DivNum;				/*!< テクスチャの分割数 */
			DirectX::XMINT2 m_ActiveTextureIndex;	/*!< 使用するテクスチャのインデックス */
			DirectX::XMFLOAT2 m_TilingRatio;		/*!< タイリングする際の割合 */
			Mode m_eMode;
			float m_Alpha;


	};

}

/*! Direct3D11関連の名前空間 */
namespace D3D11 {

	/*! 描画関連の名前空間に含める */
	namespace Graphic {

		/****************************************/
		/*		スプライトで扱う構造体			*/
		/****************************************/

		/*!
			@brief	スプライトの頂点構造体
		*/
		struct SpriteVertex
			:public VARTEX_BASE
		{
			SpriteVertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 uv) {
				m_Pos = pos, m_UV = uv;
			}
			DirectX::XMFLOAT2 m_UV;/*< UV座標 */
		};

		/*!
			@brief	スプライトのコンスタントバッファ構造体
		*/
		struct SpriteShaderBuffer
			:CONSTANT_BUFFER_BASE
		{
			ALIGN16<DirectX::XMFLOAT3>	m_Color;	/*< カラー */
			ALIGN16<float>				m_Alpha;	/*< アルファ値 */
		};
	}
}