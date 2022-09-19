
#include "ShaderInfo.fx"

struct Vertex3D
{
	// 변수 뒤에 : 레지스터이름 + 번호 로 지정한다.
	// 번호를 안붙이면 0으로 지정된다.
	float3 Pos : POSITION; // Vector3타입.
	float3 Normal : NORMAL;
	float2 UV : TEXCOORD;
};

struct Vertex3DOutput
{
	// SV가 붙으면 System Value이다. 이 값은 레지스터에 저장만 하고
	// 가져다 사용하면 안된다.
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD;
	float4 ProjPos : POSITION;
};

//Texture2DMS<float4>	g_TargetEffectTex : register(t30);
//Texture2DMS<float4> g_GBufferDepth : register(t31);

float4 PaperBurnEffect(float4 Color, float2 UV)
{
	if (Color.a == 0.f)
		return Color;

	float4 BurnColor = g_PaperBurnTexture.Sample(g_LinearSmp, UV);

	float4	result = Color;

	if (g_PaperBurnInverse == 0)
	{
		if (g_PaperBurnFilter >= BurnColor.r)
			result.a = 0.f;

		else
		{
			if (g_PaperBurnFilter - g_PaperBurnOutFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnOutFilter)
				result = g_PaperBurnOutLineColor;

			if (g_PaperBurnFilter - g_PaperBurnCenterFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnCenterFilter)
				result = g_PaperBurnCenterLineColor;

			if (g_PaperBurnFilter - g_PaperBurnInFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnInFilter)
				result = g_PaperBurnInLineColor;
		}
	}

	else
	{
		if (g_PaperBurnFilter < BurnColor.r)
			result.a = 0.f;

		else
		{
			if (g_PaperBurnFilter - g_PaperBurnOutFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnOutFilter)
				result = g_PaperBurnOutLineColor;

			if (g_PaperBurnFilter - g_PaperBurnCenterFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnCenterFilter)
				result = g_PaperBurnCenterLineColor;

			if (g_PaperBurnFilter - g_PaperBurnInFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnInFilter)
				result = g_PaperBurnInLineColor;
		}
	}

	result.a *= Color.a;

	return result;
}

Vertex3DOutput EffectVS(Vertex3D input)
{
	Vertex3DOutput output = (Vertex3DOutput)0;

	float3 Pos = input.Pos;

	output.ProjPos = mul(float4(Pos, 1.f), g_matWVP);
	output.Pos = output.ProjPos;
	output.UV = input.UV;

	return output;
}

PSOutput_Single EffectPS(Vertex3DOutput input)
{
	PSOutput_Single output = (PSOutput_Single)0;

   /* float2 ScreenUV = input.ProjPos.xy / input.ProjPos.w;
	ScreenUV = ScreenUV * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	int2 TargetPos = (int2)0;

	TargetPos.x = (int)(input.UV.x * g_Resolution.x);
	TargetPos.y = (int)(input.UV.y * g_Resolution.y);*/

	//float4 BaseTextureColor = g_TargetEffectTex.Load(Pos, 0);

	float4	BaseTextureColor = g_BaseTexture.Sample(g_BaseSmp, input.UV);

	if (BaseTextureColor.a == 0.f || g_MtrlOpacity == 0.f)
		clip(-1);

	/*float4 Depth = g_GBufferDepth.Load(TargetPos, 0);

	float Alpha = 1.f;

	if (Depth.a > 0.f)
		Alpha = (Depth.g - input.ProjPos.w) / 0.5f;

	Alpha = clamp(Alpha, 0.f, 1.f);*/

	float4 EffectColor;

	if (g_MtrlPaperBurnEnable)
	{
		EffectColor = PaperBurnEffect(float4(BaseTextureColor.rgb * g_MtrlBaseColor.rgb, BaseTextureColor.a), input.UV);
	}
	else
	{
		EffectColor = BaseTextureColor;
	}

	EffectColor.a = EffectColor.a * g_MtrlOpacity;

	output.Color = EffectColor;

	return output;
}