//グローバル

Texture2D g_Texture: register(t0);
SamplerState g_Sampler : register(s0);

cbuffer global
{
	//matrix g_WVP; //ワールドから射影までの変換行列
	matrix g_World;		/*!< ワールド行列 */
	matrix g_View;		/*!< ビュー行列 */
	matrix g_Projection;/*!< プロジェクション行列 */
	int2 g_DivNum;	/*!< テクスチャの分割数 */
	int2 g_useIndexUV;/*!< 分割したテクスチャの描画インデックス */
};
//構造体
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD;
};

//
//
//バーテックスシェーダー
PS_INPUT VS( float4 Pos : POSITION ,float2 UV : TEXCOORD) 
{
	PS_INPUT Out;
	matrix m = mul(mul(g_World, g_View), g_Projection);
	//matrix m = g_WVP;
	Out.Pos = mul(Pos, m);
	//m = transpose(m);
	Out.UV=UV;

	return Out;
}
//
//
//ピクセルシェーダー
float4 PS( PS_INPUT Input ) : SV_Target
{
	return g_Texture.Sample( g_Sampler, Input.UV );
}