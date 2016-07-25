void main_vp(in float4   position  : SV_Position,
	in float2   uv : TEXCOORD0,
	in float4   color : COLOR0,

	out float4 oPosition : SV_Position,
	out float2 oUv : TEXCOORD0,
	out float4 oColor : TEXCOORD1)
{
	oPosition = position;
	oUv = uv;
	oColor = color;
}

Texture2D <float4>  myTex;

float4 main_fp(float4 position : SV_Position,
	float2 uv : TEXCOORD0,
	float4 color : TEXCOORD1,
	SamplerState  atlas : register(s0)): SV_TARGET
{
	return myTex.Sample(atlas, uv) * color;
}


//struct VertexShaderOutput
//{
//	float4 Position : POSITION0;
//};



//struct PsInput
//{
//	float4 v4Pos : SV_POSITION;
//	float2 v2Tex : TEXTURE0;
//};
//
//Texture2D    g_Texture : register(t0);
//SamplerState g_Sampler : register(s0);
//
//float4 main_fp(PsInput Input) : SV_Target
//{
//	return g_Texture.Sample(g_Sampler, Input.v2Tex);
//}
