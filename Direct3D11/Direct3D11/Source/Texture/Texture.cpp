#include "Texture.h"
#include "../Direct3D11/Direct3D11.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
#include "../WindowsImagingComponent/WICTextureLoader.h"

/*!
	wincodec.hのCreateDecoderFromFilenameの引数がマルチバイト文字列の引数のため
	UNICODE設定でもマルチバイト文字を使う必要がある
*/

/*!
	@brief	名前空間
	@detail	usingディレクティブ
*/
using namespace D3D11;
using namespace API;
using namespace DirectX;


/*!
	@brief	コンストラクタ
*/
Texture::Texture()
{
	SecureZeroMemory(this, sizeof(this));
	m_pSamplerState		= nullptr;
	m_pResorceTexture	= nullptr;
	m_eTileMode			= TileMode::Clamp;
	m_eFilteringMode	= FilteringMode::Trilinear;
}

/*!
	@brief	デストラクタ
*/
Texture::~Texture()
{
	Finalize();
}

/*!
	@brief	初期化
	@detail	現在設定されているタイリングモードとフィルタリングモードを設定する
*/
HRESULT Texture::Initialize() 
{
	return SetTileAndFiltering(m_eTileMode, m_eFilteringMode);
}

/*!
	@brief		初期化
	@detail		タイリングモードを変更し、サンプラーを作りなおす
	@param[in]	設定するタイリングモード
*/
HRESULT Texture::Initialize(TileMode tileMode)
{
	return SetTileAndFiltering(tileMode, m_eFilteringMode);
}

/*!
	@brief		初期化
	@detail		フィルタリングモードを変更し、サンプラーを作りなおす
	@param[in]	設定するフィルタリングモード
*/
HRESULT Texture::Initialize(FilteringMode filteringMode)
{
	return SetTileAndFiltering(m_eTileMode, filteringMode);
}

/*!
	@brief		初期化
	@detail		タイリングモードとフィルタリングモードを変更し、サンプラーを作りなおす
	@param[in]	設定するタイリングモード
	@param[in]	設定するフィルタリングモード
*/
HRESULT Texture::Initialize(TileMode tileMode, FilteringMode filteringMode)
{
	return SetTileAndFiltering(tileMode, filteringMode);
}

/*!
	@brief		初期化
	@detail		テクスチャのロードとサンプラーの生成を兼ねる
	@param[in]	ロードするテクスチャのファイルパス
	@param[in]	ロードする画像のサイズ
*/
HRESULT API::Texture::Initialize(std::string filePath, DirectX::XMINT2 size)
{
	return Load(filePath, size);
}

/*!
	@brief	テクスチャデータの読み込み
	@detail	テクスチャデータの明示的なロード関数
*/
HRESULT Texture::Load(std::string filePath, DirectX::XMINT2 size)
{
	HRESULT hr;

	/*! UNICODEとマルチバイト文字列の両対応用コード */
	//auto s_path = To_TString(filePath);
	//const auto path = const_cast<LPTSTR>(s_path.c_str());

	/*! D3D11CompileFromFileの引数はマルチバイト */
	auto tmp = To_WString(filePath);
	auto path = const_cast<LPCWSTR>(tmp.c_str());


	m_Size = size;

	/*! サンプラーが生成されていなければ生成する */
	if (!m_pSamplerState) {
		SetTileAndFiltering(m_eTileMode, m_eFilteringMode);
	}

	/*! ローカル変数 */
	ID3D11Resource* pResource = nullptr;

	/*! テクスチャの生成 */
	hr = CreateWICTextureFromFile(
		Direct3D11::GetInstance().GetDevice(),
		path,
		&pResource,
		m_pResorceTexture.GetAddressOf()
	);

	/*! ローカル変数のメモリ開放 */
	if (pResource != nullptr) {
		pResource->Release();
	}
	if (FAILED(hr)) {
		std::string error = "\"" + filePath + "\" is not load in texture!";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! 読み込みの正常終了 */
	return S_OK;
}

/*!
	@brief	ファイナライズ
	@detail	COMポインタを使用しているのでResetの明示的な呼び出し
*/
void Texture::Finalize()
{
	m_pSamplerState.Reset();
	m_pResorceTexture.Reset();
}

/*!
	@brief		タイリングモードとフィルタリングモードの設定
	@param[in]	設定するタイルモード
	@param[in]	設定するフィルタリング(アドレッシングモード)
	@detail		サンプラーステートの作成
*/
HRESULT Texture::SetTileAndFiltering(TileMode tile, FilteringMode filter)
{
	/*! 引数の保持 */
	m_eTileMode			= tile;
	m_eFilteringMode	= filter;

	/*! サンプラーステート設定 */
	D3D11_SAMPLER_DESC sd;
	SecureZeroMemory(&sd, sizeof(sd));
	sd.Filter = static_cast<D3D11_FILTER>(m_eFilteringMode);			/*!< フィルタリング */
	sd.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< アドレッシングモード */
	sd.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< アドレッシングモード */
	sd.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< アドレッシングモード */

	HRESULT hr;
	/*! サンプラー作成 */
	hr= Direct3D11::GetInstance().GetDevice()->CreateSamplerState(
		&sd,
		m_pSamplerState.GetAddressOf()
	);
	if (FAILED(hr)) {
		std::string error = "Sampler state is not created!";
		ErrorLog(error);
		return E_FAIL;
	}
	return S_OK;
}
