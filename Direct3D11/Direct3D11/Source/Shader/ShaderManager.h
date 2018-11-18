/*
	@file	ShaderManager.h
	@date	2018/03/04
	@author	番場 宥輝
	@brief	シェーダー関連
	@detail	vector,mapの注意:http://msty.hatenablog.jp/entry/2016/08/18/144934
*/
#pragma once
#include <D3D11.h>
#include <map>
#include <wrl/client.h>
#include "../Singleton/Singleton.h"
#include "../MemoryLeaks.h"

#if defined DEBUG||_DEBUG
# define DEBUG_SHADER
#endif

/*! Direct3D11関連 */
namespace D3D11 {

	/*! 描画関連の名前空間に含める */
	namespace Graphic {

		/*!
			@brief	シェーダーを構成する構造体
		*/
		struct ShaderData
		{
		public:
			/*!
				@brief	コンストラクタ
			*/
			ShaderData(){
				SecureZeroMemory(this, sizeof(this));
				m_pVertexLayout		= nullptr;
				m_pVertexShader		= nullptr;
				m_pPixelShader		= nullptr;
				m_pConstantBuffer	= nullptr;
			}
			/*!
				@brief	デストラクタ
			*/
			~ShaderData()
			{
				//if (m_pVertexLayout != nullptr) { m_pVertexLayout->Release(); }
				//m_pVertexLayout = nullptr;
				//if (m_pVertexShader != nullptr) { m_pVertexShader->Release(); }
				//m_pVertexShader = nullptr;
				//if (m_pPixelShader != nullptr) { m_pPixelShader->Release(); }
				//m_pPixelShader = nullptr;
				//if (m_pConstantBuffer != nullptr) { m_pConstantBuffer->Release(); }
				//m_pConstantBuffer = nullptr;

				//if (m_pVertexLayout != NULL) { m_pVertexLayout->Release(); }
				//m_pVertexLayout = NULL;
				//if (m_pVertexShader != NULL) { m_pVertexShader->Release(); }
				//m_pVertexShader = NULL;
				//if (m_pPixelShader != NULL) { m_pPixelShader->Release(); }
				//m_pPixelShader = NULL;
				//if (m_pConstantBuffer != NULL) { m_pConstantBuffer->Release(); }
				//m_pConstantBuffer = NULL;

				m_pVertexLayout.Reset();
				m_pVertexShader.Reset();
				m_pPixelShader.Reset();
				m_pConstantBuffer.Reset();
			};

			Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_pVertexLayout;	/*< インプットレイアウト */
			Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_pVertexShader;	/*< 頂点シェーダー */
			Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pPixelShader;		/*< ピクセルシェーダー */
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_pConstantBuffer;	/*< コンスタントバッファー */
		};

		/*!
			@brief	シェーダー管理クラス
			@detail	シェーダーを作成せずとも描画出来るデフォルトシェーダーを用意する
		*/
		class ShaderManager
			:public Singleton<ShaderManager>
		{
		public:
			~ShaderManager();

			static const std::string c_SpriteDefault;
			static const std::string c_MeshDefault;

			HRESULT AddNewShaderData(std::string szKeyName, ShaderData* pNewShaderData);	/*!< 構造体をリストに追加登録 */
			HRESULT Initialize();
			void Finalize();
			HRESULT MakeShader(std::string szFileName, std::string szFuncName, std::string szProfileName, void** ppShader, ID3DBlob** ppBlob);
			ShaderData* GetShaderData(std::string szKeyName);

		private:
			ShaderManager();
			friend class Singleton<ShaderManager>;

			ShaderData* m_pAddDataRef;/*!< データ追加用の参照メンバ */
			std::map<std::string, ShaderData*>m_pShaderDataMap;

		};

	}
}
