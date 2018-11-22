#include "ITexture.h"
#include "../Direct3D11/Direct3D11.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
#include "../WindowsImagingComponent/WICTextureLoader.h"

/*!
	@brief	名前空間
	@detail	usingディレクティブ
*/
using namespace D3D11;
using namespace DirectX;

/*!
	@brief	コンストラクタ
	@detail	メンバ変数の初期化を行う
*/
API::Base::ITexture::ITexture() :
	m_pShaderResourceView(nullptr),
	m_pSamplerState(nullptr),
	m_eTileMode(TileMode::Clamp),
	m_eFilterMode(FilteringMode::Trilinear)
{
}

/*!
	@brief	仮想デストラクタ
	@detail	空デストラクタ
*/
API::Base::ITexture::~ITexture()
{
}

/*!
	@fn		ファイナライズ
	@brief	破棄処理
	@detail	メンバの明示的な開放
			派生先でメンバが増えることを踏まえ、仮想関数として実装

*/
void API::Base::ITexture::Finalize()
{
	//m_pShaderResourceView.Reset();
	//m_pSamplerState.Reset();
}

/*!
	@fn			タイリングモードとフィルタリングモードのセッター
	@brief		タイリングモードとフィルタリングモードの設定
	@param[in]	設定するタイルモード
	@param[in]	設定するフィルタリング(アドレッシングモード)
	@detail		サンプラーステートを作成
*/
HRESULT API::Base::ITexture::SetTileAndFiltering(const TileMode tileMode, const FilteringMode filterMode)
{
	/*! 引数の保持 */
	m_eTileMode = tileMode;
	m_eFilterMode = filterMode;

	/*! サンプラーステート設定 */
	D3D11_SAMPLER_DESC sd;
	SecureZeroMemory(&sd, sizeof(sd));
	sd.Filter = static_cast<D3D11_FILTER>(m_eFilterMode);				/*!< フィルタリング */
	sd.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< アドレッシングモード */
	sd.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< アドレッシングモード */
	sd.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(m_eTileMode);	/*!< アドレッシングモード */

	HRESULT hr;
	/*! サンプラー作成 */
	hr = Direct3D11::GetInstance().GetDevice()->CreateSamplerState(
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

/*!
	@fn			画像の読み込み
	@brief		画像の読み込みを行いSRVを作成
	@detail		画像データからSRVを作成し、メンバ変数にバインド
	@param[in]	読み込むファイルのパス
	@return		読み取り結果 成功:S_OK  失敗:E_FAIL
*/
HRESULT API::Base::ITexture::Load(std::string filePath)
{
	HRESULT hr;

	/*! 
		D3D11CompileFromFileの引数はマルチバイトなので
		受け取ったパスをマルチバイトに変換
	*/
	auto cast = To_WString(filePath);
	auto path = const_cast<LPCWSTR>(cast.c_str());

	//!	ローカル変数
	Microsoft::WRL::ComPtr<ID3D11Resource> pResource = nullptr;

	/*! テクスチャ作成 */
	hr = CreateWICTextureFromFile(
		Direct3D11::GetInstance().GetDevice(),
		path,
		pResource.GetAddressOf(),
		m_pShaderResourceView.GetAddressOf()
	);

	/*! ローカル変数のメモリ開放 */
	if (pResource.Get() != nullptr) {
		pResource.Reset();
	}
	if (FAILED(hr)) {
		std::string error = "\"" + filePath + "\" is not load in texture!";
		ErrorLog(error);
		return E_FAIL;
	}

	/*! 読み込みの正常終了 */
	return S_OK;
}
