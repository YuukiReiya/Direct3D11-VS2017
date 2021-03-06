#pragma comment(lib,"d3dCompiler.lib")

#include <d3dcompiler.h>
#include <string>

#include "../Direct3D11/Direct3D11.h"
#include "ShaderManager.h"
#include "../MemoryLeaks.h"
#include "../MyGame.h"
#include "../Sprite/Sprite.h"

/*!
	@brief	名前空間
	@detail	usingディレクティブ
*/
using namespace D3D11;
using namespace D3D11::Graphic;

/*!
	@def	定数宣言
*/
const std::string ShaderManager::c_SpriteDefault = "SPRITE_DEFAULT";/*!< スプライトシェーダーのデフォルト設定 */
const std::string ShaderManager::c_MeshDefault	 = "MESH_DEFAULT";	/*!< メッシュシェーダーのデフォルト設定 */
const std::string c_ResourceHierarchy	= "Resource/Shader/";		/*!< シェーダーのリソースがおいてある階層までのパス */
const std::string c_VertexProfile		= "vs";						/*!< 頂点シェーダー */
const std::string c_PixelProfile		= "ps";						/*!< ピクセルシェーダー */
const std::string c_GeometryProfile		= "gs";						/*!< ジオメトリシェーダー */
const std::string c_HullProfile			= "hs";						/*!< ハルシェーダー */
const std::string c_DomainProfile		= "ds";						/*!< ドメインシェーダー */
const std::string c_ComputeProfile		= "cs";						/*!< コンピュートシェーダー */
constexpr int c_ShaderModelStringArraySize	= 3;					/*!< シェーダーモデルの設定文字列(\0含む)の配列のサイズ ※上記Profileの文字列サイズ+終端文字分 */

/*!
	@brief	コンストラクタ
*/
ShaderManager::ShaderManager() 
{

}

/*!
	@brief	デストラクタ
*/
ShaderManager::~ShaderManager()
{
	Finalize();
}

/*!
	@brief	初期化
*/
HRESULT ShaderManager::Initialize()
{
	HRESULT hr;
	ID3DBlob* pCompiledShader = NULL;/*!< コンパイル用ブロブ */

	/*! スプライト用のデフォルト設定作成 */
	m_pAddDataRef = new ShaderData;
	{
		/*! バーテックスシェーダーの作成 */
		hr = MakeShader("DefaultSprite.hlsl", "VS", "vs_5_0", (void**)&m_pAddDataRef->m_pVertexShader, &pCompiledShader);
		if (FAILED(hr)) {
			ErrorLog("\"SpriteDefault\" vertex shader is not create!");
			return E_FAIL;
		}

		/*! 頂点インプットレイアウト定義 */
		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		uint32_t numElements = sizeof(layout) / sizeof(*layout);/*!< ポインタ */

		/*! 頂点インプットレイアウトを作成 */
		hr = Direct3D11::GetInstance().GetDevice()->CreateInputLayout(
			layout,
			numElements,
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			&m_pAddDataRef->m_pVertexLayout
		);
		if (FAILED(hr)) {
			ErrorLog("\"SpriteDefault\" input layout is not create!");
			return E_FAIL;
		}

		/*! ピクセルシェーダーの作成 */
		hr = ShaderManager::MakeShader("DefaultSprite.hlsl", "PS", "ps_5_0", (void**)&m_pAddDataRef->m_pPixelShader, &pCompiledShader);
		if (FAILED(hr)) {
			ErrorLog("\"SpriteDefault\" pixel shader is not create!");
			return E_FAIL;
		}

		/*! コンスタントバッファ定義 */
		D3D11_BUFFER_DESC cb;
		SecureZeroMemory(&cb, sizeof(cb));
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.ByteWidth = sizeof(SpriteShaderBuffer);
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.CPUAccessFlags = 0;
		cb.Usage = D3D11_USAGE_DYNAMIC;
		cb.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

		/*! コンスタントバッファ作成 */
		hr = Direct3D11::GetInstance().GetDevice()->CreateBuffer(&cb, NULL, &m_pAddDataRef->m_pConstantBuffer);
		if (FAILED(hr)) {
			std::string error = "\"SpriteDefault\" ConstantBuffer is not create!";
			ErrorLog(error);
			return E_FAIL;
		}

	}
	AddNewShaderData(c_SpriteDefault, m_pAddDataRef);
	
	/*! ブロブの解放 */
	pCompiledShader->Release();
	pCompiledShader = NULL;

	/*! メッシュ用のデフォルト設定 */
	//m_pAddDataRef = new ShaderData;
	{
		///*! バーテックスシェーダーの作成 */
		//hr = MakeShader("DefaultMesh.hlsl", "VS", "vs_5_0", (void**)&m_pAddDataRef->m_pVertexShader, &pCompiledShader);
		//if (FAILED(hr)) {
		//	ErrorLog("\"MeshDefault\" vertex shader is not create!");
		//	return E_FAIL;
		//}

		///*! 頂点インプットレイアウト定義 */
		//D3D11_INPUT_ELEMENT_DESC layout[] = {
		//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//};
		//uint32_t numElements = sizeof(layout) / sizeof(*layout);/*!< ポインタ */
		//
		///*! 頂点インプットレイアウトを作成 */
		//hr = Direct3D11::GetInstance().GetDevice()->CreateInputLayout(
		//	layout,
		//	numElements,
		//	pCompiledShader->GetBufferPointer(),
		//	pCompiledShader->GetBufferSize(),
		//	&m_pAddDataRef->m_pVertexLayout
		//);

		///*! ピクセルシェーダーの作成 */
		//hr = ShaderManager::MakeShader("DefaultMesh.hlsl", "PS", "ps_5_0", (void**)&m_pAddDataRef->m_pPixelShader, &pCompiledShader);
		//if (FAILED(hr)) {
		//	ErrorLog("\"MeshDefault\" pixel shader is not create!");
		//	return E_FAIL;
		//}

		///*! コンスタントバッファ定義 */
		//D3D11_BUFFER_DESC cb;
		//cb.ByteWidth = sizeof(MeshShaderBuffer);
		//cb.Usage = D3D11_USAGE_DYNAMIC;
		//cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		//cb.MiscFlags = 0;
		//cb.StructureByteStride = 0;

		///*! コンスタントバッファ作成 */
		//hr = Direct3D11::GetInstance().GetDevice()->CreateBuffer(&cb, NULL, &m_pAddDataRef->m_pConstantBuffer);
		//if (FAILED(hr)) {
		//	std::string error = "\"MeshDefault\" ConstantBuffer is not create!";
		//	ErrorLog(error);
		//	return E_FAIL;
		//}

	}
	//AddNewShaderData(c_MeshDefault, m_pAddDataRef);

	return S_OK;
}

/*!
	@brief	終了処理
*/
void ShaderManager::Finalize()
{
	for (auto it : m_pShaderDataUMap) {
		delete it.second;
	}
	m_pShaderDataUMap.clear();
	m_pAddDataRef = nullptr;
}


/*!
	@brief	新たなシェーダーデータをクラスに登録する
	@detail	各メンバ変数の初期化は行わないので各自で初期化及び生成しておく
*/
HRESULT ShaderManager::AddNewShaderData(std::string szKeyName, ShaderData * pNewShaderData)
{
	/*! 登録可能か判定 */
	bool isFound = m_pShaderDataUMap.find(szKeyName) == m_pShaderDataUMap.end();

	/*! 登録しようとしたキー名は既に登録済みのため追加しない */
	if (!isFound) { return E_FAIL; }

	/*! キー名でリスト(map)に追加 */
	m_pShaderDataUMap[szKeyName] = pNewShaderData;

	return S_OK;
}

/*!
	@brief	シェーダーの作成
	@return	成功有無
*/
HRESULT ShaderManager::MakeShader(std::string szFileName, std::string szFuncName, std::string szProfileName, void ** ppShader, ID3DBlob ** ppBlob)
{
	/*! UNICODE、マルチバイト両対応用文字列変換 */
	std::string sFilePath = c_ResourceHierarchy + szFileName;

	//auto tmp = To_TString(sFilePath);
	//auto path = const_cast<LPCWSTR>(tmp.c_str());

	/*! D3D11CompileFromFileの引数はマルチバイト */
	auto tmp = To_WString(sFilePath);
	auto path = const_cast<LPCWSTR>(tmp.c_str());

	DWORD shaderFlags;
#ifdef DEBUG_SHADER
	shaderFlags = D3DCOMPILE_DEBUG;
#else
	shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#endif

	HRESULT hr;

	LPCSTR funcName		= szFuncName.c_str();
	LPCSTR profileName	= szProfileName.c_str();

	/*! ブロブのコンパイル */
	ID3DBlob* pErrors = NULL;
	hr = D3DCompileFromFile(
		path,
		NULL,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		funcName,
		profileName,
		shaderFlags,
		NULL,
		ppBlob,
		&pErrors
	);
	if (FAILED(hr)) {
		std::string bufferError = (char*)pErrors->GetBufferPointer();
		std::string error = "\"" + sFilePath + "\" is not compile from file!\n" + bufferError;
		ErrorLog(error);
		return E_FAIL;
	}
	if (pErrors != NULL) {
		pErrors->Release();
		pErrors = NULL;
	}

	char szProfile[c_ShaderModelStringArraySize] = { 0 };

	/*! 終端文字を含まないバッファのメモリを変数にコピー */
	strncpy_s(szProfile, profileName, (c_ShaderModelStringArraySize - 1));/*!< 終端文字のバッファーを一つ確保しておく */

	/*! 頂点シェーダー(Vertex Shader) */
	if (strcmp(szProfile, c_VertexProfile.c_str()) == 0) {
		hr = Direct3D11::GetInstance().GetDevice()->CreateVertexShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11VertexShader**)ppShader);
		if (FAILED(hr)) {
			std::string error = "\"" + szFileName + "\" is not matched \"Vertex Shader\"!";
			ErrorLog(error);
			return E_FAIL;
		}
		else return S_OK;
	}
	/*! ピクセルシェーダー(Pixel Shader) */
	if (strcmp(szProfile, c_PixelProfile.c_str()) == 0) {
		hr = Direct3D11::GetInstance().GetDevice()->CreatePixelShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11PixelShader**)ppShader);
		if (FAILED(hr)) {
			std::string error = "\"" + szFileName + "\" is not matched \"Pixel Shader\"!";
			ErrorLog(error);
			return E_FAIL;
		}
		else return S_OK;
	}
	/*! ジオメトリシェーダー(Geometry Shader) */
	if (strcmp(szProfile, c_GeometryProfile.c_str()) == 0) {
		hr = Direct3D11::GetInstance().GetDevice()->CreateGeometryShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11GeometryShader**)ppShader);
		if (FAILED(hr)) {
			std::string error = "\"" + szFileName + "\" is not matched \"Geometry Shader\"!";
			ErrorLog(error);
			return E_FAIL;
		}
		else return S_OK;
	}
	/*! ハルシェーダー(Hull Shader) */
	if (strcmp(szProfile, c_HullProfile.c_str()) == 0) {
		hr = Direct3D11::GetInstance().GetDevice()->CreateHullShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11HullShader**)ppShader);
		if (FAILED(hr)) {
			std::string error = "\"" + szFileName + "\" is not matched \"Hull Shader\"!";
			ErrorLog(error);
			return E_FAIL;
		}
		else return true;
	}
	/*! ドメインシェーダー(Domain Shader) */
	if (strcmp(szProfile, c_DomainProfile.c_str()) == 0) {
		hr = Direct3D11::GetInstance().GetDevice()->CreateDomainShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11DomainShader**)ppShader);
		if (FAILED(hr)) {
			std::string error = "\"" + szFileName + "\" is not matched \"Domain Shader\"!";
			ErrorLog(error);
			return E_FAIL;
		}
		else return S_OK;
	}
	/*! コンピュートシェーダー(Compute Shader) */
	if (strcmp(szProfile, c_ComputeProfile.c_str()) == 0) {
		hr = Direct3D11::GetInstance().GetDevice()->CreateComputeShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11ComputeShader**)ppShader);
		if (FAILED(hr)) {
			std::string error = "\"" + szFileName + "\" is not matched \"Compute Shader\"!";
			ErrorLog(error);
			return E_FAIL;
		}
		else return S_OK;
	}
	std::string error = "\"ProfileName\" is not ShaderModel!";
	ErrorLog(error);
	return E_FAIL;
}

/*!
	@brief	キー(文字列)から登録済みのシェーダー情報を取得する
	@detail	探索文字列から情報を取得することに失敗した場合NULLを返す
*/
ShaderData * ShaderManager::GetShaderData(std::string szKeyName)
{
	return m_pShaderDataUMap[szKeyName];
}

