
struct PSOutput_Single
{
	float4	Color : SV_TARGET;
};

struct PSOutput_Single1
{
	float4	Color : SV_TARGET;
	float2	UV : TEXCOORD;
};

struct PSOutput_GBuffer
{
	float4 Diffuse : SV_Target;
	float4 GBuffer1 : SV_Target1;
	float4 GBuffer2 : SV_Target2;
	float4 GBuffer3 : SV_Target3;
	float4 GBuffer4 : SV_Target4;
	float4 GBuffer5 : SV_Target5;
};

cbuffer Transform : register(b0)
{
	matrix	g_matWorld;
	matrix	g_matView;
	matrix	g_matProj;
	matrix  g_matInvProj;
	matrix	g_matWV;
	matrix	g_matWVP;
	matrix	g_matVP;
	matrix g_matInvVP;
	matrix g_matInvWVP;
	matrix	g_matPrevWorld;
	matrix	g_matPrevView;
	float3	g_Pivot;
	float	g_TransformEmpty1;
	float3	g_MeshSize;
	float	g_TransformEmpty;
};

cbuffer Material : register(b1)
{
	float4  g_MtrlBaseColor;
	float4  g_MtrlAmbientColor;
	float4  g_MtrlSpecularColor;
	float4  g_MtrlEmissiveColor;
	float	g_MtrlOpacity;
	int		g_MtrlPaperBurnEnable;
	int		g_MtrlBumpEnable;
	int		g_MtrlAnimation3DEnable;
	int		g_MtrlSpecularTex;
	int		g_MtrlEmissiveTex;
	int		g_MtrlReceiveDecal;
	float	g_MtrlEmpty;
};

cbuffer Standard2D : register(b2)
{
	int		g_Animation2DEnable;
	float3	g_Standard2DEmpty;
};

cbuffer	GlobalCBuffer : register(b3)
{
	float	g_DeltaTime;
	float	g_AccTime;
	float2	g_Resolution;
	float2	g_NoiseResolution;
	float2	g_GlobalEmpty;
};

cbuffer PaperBurnCBuffer : register(b4)
{
	float4	g_PaperBurnInLineColor;
	float4	g_PaperBurnOutLineColor;
	float4	g_PaperBurnCenterLineColor;
	float	g_PaperBurnFilter;
	int		g_PaperBurnInverse;
	float	g_PaperBurnInFilter;
	float	g_PaperBurnOutFilter;
	float	g_PaperBurnCenterFilter;
	float3	g_PaperBurnEmpty;
};

cbuffer LightCBuffer : register(b5)
{
	float4 g_LightColor;
	int g_LightType;
	float3 g_LightPos;
	float3 g_LightDir;
	float g_LightDistance;
	float g_LightAngleIn;
	float g_LightAngleOut;
	float g_LightAtt1;
	float g_LightAtt2;
	float g_LightAtt3;
	float3 g_LightEmpty;
};

cbuffer InstancingCBuffer : register(b6)
{
	int g_InstancingBoneCount;
	float3 g_InstancingEmpty;
};

struct LightResult
{
	float3 Dif;
	float3 Amb;
	float3 Spc;
	float3 Emv;
};

#define	LightTypeDir	0
#define	LightTypePoint	1
#define	LightTypeSpot	2



SamplerState	g_PointSmp : register(s0);
SamplerState	g_LinearSmp : register(s1);
SamplerState	g_AnisotropicSmp : register(s2);

SamplerState	g_BaseSmp : register(s3);

Texture2D g_BaseTexture : register(t0);
Texture2D g_NormalTexture : register(t1);
Texture2D g_SpecularTexture : register(t2);
Texture2D g_EmissiveTexture : register(t3);

Texture2D<float4>		g_NoiseTexture	: register(t100);
Texture2D				g_PaperBurnTexture	: register(t101);

StructuredBuffer<float>	g_RandBuffer	: register(t90);

static const float Weight[12] =
{
	0.0561f, 0.1353f, 0.278, 0.4868, 0.7261, 0.9231,
	1.f, 0.9231f, 0.7261, 0.4868, 0.1353, 0.0561
};

static const float Total = 6.2108;

static const float2 g_NullPos[4] =
{
	float2(-1.f, 1.f),
	float2(1.f, 1.f),
	float2(-1.f, -1.f),
	float2(1.f, -1.f)
};

static const float2 g_NullUV[4] =
{
	float2(0.f, 0.f),
	float2(1.f, 0.f),
	float2(0.f, 1.f),
	float2(1.f, 1.f)
};



static float Gaussian5x5[25] =
{
	0.003765f, 0.015019f, 0.023792f, 0.015019f, 0.003765f,
	0.015019f, 0.059912f, 0.094907f, 0.059912f, 0.015019f,
	0.023792f, 0.094907f, 0.150342f, 0.094907f, 0.023792f,
	0.015019f, 0.059912f, 0.094907f, 0.059912f, 0.015019f,
	0.003765f, 0.015019f, 0.023792f, 0.015019f, 0.003765f
};

float GaussianSample(int2 UV, Texture2D Tex)
{
	float	Output = 0.f;

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			int2	ConvertUV = UV + int2(j - 2, i - 2);

			if (ConvertUV.x < 0)
				ConvertUV.x = 0;

			else if (ConvertUV.x > g_NoiseResolution.x)
				ConvertUV.x = g_NoiseResolution.x - 1;

			if (ConvertUV.y < 0)
				ConvertUV.y = 0;

			else if (ConvertUV.y > g_NoiseResolution.y)
				ConvertUV.y = g_NoiseResolution.y - 1;

			Output += Tex[ConvertUV].r * Gaussian5x5[i * 5 + j];
		}
	}

	return Output;
}

float Rand(float Key)
{
	float2	UV = float2(cos(Key + g_AccTime), sin(g_AccTime));
	
	UV = frac(UV);

	return GaussianSample(UV * g_NoiseResolution, g_NoiseTexture);
}

float DegreeToRadian(float Angle)
{
	return Angle / 180.f * 3.14159f;
}


float4 PaperBurn2D(float4 Color, float2 UV)
{
	if (g_MtrlPaperBurnEnable == 0)
		return Color;
	
	else if (Color.a == 0.f)
		return Color;

	float4 BurnColor = g_PaperBurnTexture.Sample(g_LinearSmp, UV);

	float4	result = Color;

	if (g_PaperBurnInverse == 0)
	{
		if (g_PaperBurnFilter >= BurnColor.r)
			result.a = 0.f;

		else
		{
			if (g_PaperBurnFilter - g_PaperBurnOutFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurnFilter + g_PaperBurnOutFilter)
				result = g_PaperBurnOutLineColor;

			if (g_PaperBurnFilter - g_PaperBurnCenterFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurnFilter + g_PaperBurnCenterFilter)
				result = g_PaperBurnCenterLineColor;

			if (g_PaperBurnFilter - g_PaperBurnInFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurnFilter + g_PaperBurnInFilter)
				result = g_PaperBurnInLineColor;
		}
	}

	else
	{
		if (g_PaperBurnFilter < BurnColor.r)
			result.a = 0.f;

		else
		{
			if (g_PaperBurnFilter - g_PaperBurnOutFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurnFilter + g_PaperBurnOutFilter)
				result = g_PaperBurnOutLineColor;

			if (g_PaperBurnFilter - g_PaperBurnCenterFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurnFilter + g_PaperBurnCenterFilter)
				result = g_PaperBurnCenterLineColor;

			if (g_PaperBurnFilter - g_PaperBurnInFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurnFilter + g_PaperBurnInFilter)
				result = g_PaperBurnInLineColor;
		}
	}

	result.a *= Color.a;

	return result;
}


float3 ComputeBumpNormal(float3 Normal, float3 Tangent, float3 Binormal,
	float2 UV)
{
	float3 result = Normal;
	
	if (g_MtrlBumpEnable == 1)
	{
		float4 NormalColor = g_NormalTexture.Sample(g_BaseSmp, UV);
		
		// 색상은 0 ~ 1 사이이므로 -1 ~ 1 사이의 법선벡터로 만들어준다.
		float3 ConvertNormal = NormalColor.xyz * 2.f - 1.f;
		// z는 무조건 + 방향으로 만들어준다.
		ConvertNormal.z = 1.f;
		ConvertNormal = normalize(ConvertNormal);
		
		// Tangent, Binormal, Normal을 이용해서 위에서 만들어준 법선
		// 벡터를 뷰공간으로 변환해준다. 뷰공간이 되는 이유는 Tangent,
		// Binormal, Normal 3개 모두 뷰공간으로 변환된 벡터가 들어오기
		// 때문이다.
		float3x3 mat =
		{
			Tangent,
			Binormal,
			Normal
		};

		result = normalize(mul(ConvertNormal, mat));
	}
	
	return result;
}

float ConvertColor(float4 Color)
{
	uint4 Convert = (uint4) 0;
	
	Convert.r = uint(Color.r * 255);
	Convert.g = uint(Color.g * 255);
	Convert.b = uint(Color.b * 255);
	Convert.a = uint(Color.a * 255);

	uint Result = 0;
	
	Result = Convert.a;
	Result = (Result << 8) | Convert.r;
	Result = (Result << 8) | Convert.g;
	Result = (Result << 8) | Convert.b;
	
	return asfloat(Result);
}

float4 ConvertColor(float Color)
{
	uint Convert = asuint(Color);

	float4 Result;
	Result.b = (Convert & 0x000000ff) / 255.f;
	Result.g = ((Convert >> 8) & 0x000000ff) / 255.f;
	Result.r = ((Convert >> 16) & 0x000000ff) / 255.f;
	Result.a = ((Convert >> 24) & 0x000000ff) / 255.f;

	return Result;

}


LightResult
	ComputeLight(
	float3 Pos, float3 Normal, float3 Tangent, float3 Binormal,
	float2 UV)
{
	LightResult result = (LightResult) 0;
	
	float3 LightDir = (float3) 0.f;
	float Attn = 1.f;
	
	if (g_LightType == LightTypeDir)
	{
		LightDir = -g_LightDir;
		LightDir = normalize(LightDir);
	}
	
	
	if (g_LightType == LightTypePoint)
	{
		LightDir = g_LightPos - Pos;
		LightDir = normalize(LightDir);
		
		float Dist = distance(g_LightPos, Pos);
		
		if (Dist > g_LightDistance)
			Attn = 0.f;
		
		else
			Attn = 1.f / (g_LightAtt1 + g_LightAtt2 * Dist + g_LightAtt3 * (Dist * Dist));
	}
	
	
	if (g_LightType == LightTypeSpot)
	{
	}
	
	float3 ViewNormal = ComputeBumpNormal(Normal, Tangent, Binormal, UV);
	
	// 내적값이 음수가 나오면 0이 반환되고 양수가 나오면 해당 값이 그대로 반환된다.
	float Intensity = max(0.f, dot(ViewNormal, LightDir));
	
	result.Dif = g_LightColor.xyz * g_MtrlBaseColor.xyz * Intensity * Attn;
	result.Amb = g_LightColor.xyz * 0.2f * g_MtrlAmbientColor.xyz * Attn;
	
	float3 View = -Pos;
	View = normalize(View);
	
	// 퐁 쉐이딩
	float3 Reflect = 2.f * ViewNormal * dot(ViewNormal, LightDir) - LightDir;
	Reflect = normalize(Reflect);	
	float SpcIntensity = max(0.f, dot(View, Reflect));
	
	// 블린-퐁 쉐이딩
	//float3 Reflect = normalize(View + LightDir);
	//float SpcIntensity = max(0.f, dot(ViewNormal, Reflect));
	
	float3 SpecularColor = g_MtrlSpecularColor.xyz;
	
	if (g_MtrlSpecularTex)
		SpecularColor = g_SpecularTexture.Sample(g_BaseSmp, UV).xxx;
	
	SpecularColor = float3(0.5f, 0.5f, 0.5f);
	
	result.Spc = g_LightColor.xyz * SpecularColor * 
		pow(SpcIntensity, g_MtrlSpecularColor.w) * Attn;
	
	float3 EmissiveColor = g_MtrlEmissiveColor.xyz;
	
	if (g_MtrlEmissiveTex)
		EmissiveColor = g_EmissiveTexture.Sample(g_BaseSmp, UV).xxx;
	
	result.Emv = EmissiveColor;
	
	//result.Spc = float3(0.5f, 0.5f, 0.5f);
	result.Emv = float3(0.f, 0.f, 0.f);
	
	return result;
}
//
//float3x3 inverse(float3x3 m) {
//	float n11 = m[0][0], n12 = m[1][0], n13 = m[2][0], n14 = m[3][0];
//	float n21 = m[0][1], n22 = m[1][1], n23 = m[2][1], n24 = m[3][1];
//	float n31 = m[0][2], n32 = m[1][2], n33 = m[2][2], n34 = m[3][2];
//
//	float t11 = n23 * n34 - n24 * n33 + n24 * n32 - n22 * n34 - n23 * n32 + n22 * n33;
//	float t12 = n14 * n33 - n13 * n34 - n14 * n32 + n12 * n34 + n13 * n32 - n12 * n33;
//	float t13 = n13 * n24 - n14 * n23 + n14 * n22 - n12 * n24 - n13 * n22 + n12 * n23;
//	float t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;
//
//	float det = n11 * t11 + n21 * t12 + n31 * t13 + t14;
//	float idet = 1.0f / det;
//
//	float3x3 ret;
//
//	ret[0][0] = t11 * idet;
//	ret[0][1] = (n24 * n33 - n23 * n34 - n24 * n31 + n21 * n34 + n23 * n31 - n21 * n33) * idet;
//	ret[0][2] = (n22 * n34 - n24 * n32 + n24 * n31 - n21 * n34 - n22 * n31 + n21 * n32) * idet;
//	ret[0][3] = (n23 * n32 - n22 * n33 - n23 * n31 + n21 * n33 + n22 * n31 - n21 * n32) * idet;
//
//	ret[1][0] = t12 * idet;
//	ret[1][1] = (n13 * n34 - n14 * n33 + n14 * n31 - n11 * n34 - n13 * n31 + n11 * n33) * idet;
//	ret[1][2] = (n14 * n32 - n12 * n34 - n14 * n31 + n11 * n34 + n12 * n31 - n11 * n32) * idet;
//	ret[1][3] = (n12 * n33 - n13 * n32 + n13 * n31 - n11 * n33 - n12 * n31 + n11 * n32) * idet;
//
//	ret[2][0] = t13 * idet;
//	ret[2][1] = (n14 * n23 - n13 * n24 - n14 * n21 + n11 * n24 + n13 * n21 - n11 * n23) * idet;
//	ret[2][2] = (n12 * n24 - n14 * n22 + n14 * n21 - n11 * n24 - n12 * n21 + n11 * n22) * idet;
//	ret[2][3] = (n13 * n22 - n12 * n23 - n13 * n21 + n11 * n23 + n12 * n21 - n11 * n22) * idet;
//
//	ret[3][0] = t14 * idet;
//	ret[3][1] = (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34) * idet;
//	ret[3][2] = (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34) * idet;
//	ret[3][3] = (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33) * idet;
//
//	return ret;
//}