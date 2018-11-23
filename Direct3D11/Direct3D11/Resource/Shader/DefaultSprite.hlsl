//�O���[�o��

Texture2D g_Texture: register(t0);
SamplerState g_Sampler : register(s0);

cbuffer global
{
	//matrix g_WVP; //���[���h����ˉe�܂ł̕ϊ��s��
	matrix g_World;		/*!< ���[���h�s�� */
	matrix g_View;		/*!< �r���[�s�� */
	matrix g_Projection;/*!< �v���W�F�N�V�����s�� */
	int2 g_DivNum;	/*!< �e�N�X�`���̕����� */
	int2 g_useIndexUV;/*!< ���������e�N�X�`���̕`��C���f�b�N�X */
};
//�\����
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD;
};

//
//
//�o�[�e�b�N�X�V�F�[�_�[
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
//�s�N�Z���V�F�[�_�[
float4 PS( PS_INPUT Input ) : SV_Target
{
	return g_Texture.Sample( g_Sampler, Input.UV );
}