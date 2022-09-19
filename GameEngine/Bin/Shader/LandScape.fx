
#include "ShaderInfo.fx"

struct Vertex3DSplatting
{
	float3 Pos : POSITION;
	float3 Normal : NORMAL;
	float2 UV : TEXCOORD;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
	float4 SPLTexture : SPLTEXTURE;
	float4 SPLTexture2 : SPLTEXTURESEC;
	float4 SPLTexture3 : SPLTEXTURETHR;
	float4 SPLNormal : SPLNORMAL;
	float4 SPLNormal2 : SPLNORMALSEC;
	float4 SPLNormal3 : SPLNORMALTHR;
};

struct Vertex3DSplattingOutput
{
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD;
	float4 ProjPos : POSITION;
	float3 ViewPos : POSITION1;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
	float4 SPLTexture : SPLTEXTURE;
	float4 SPLTexture2 : SPLTEXTURESEC;
	float4 SPLTexture3 : SPLTEXTURETHR;
	float4 SPLNormal : SPLNORMAL;
	float4 SPLNormal2 : SPLNORMALSEC;
	float4 SPLNormal3 : SPLNORMALTHR;
};

cbuffer LandScape : register(b11)
{
	float g_LandScapeDetailLevel;
	int g_LandScapeSplatCount;
	float2 g_LandScapeEmpty;
	int	B_Type; // 비활성화, 원형, 사각형
	float3 B_Location;
	float B_Range;
	float3 B_Color;
};

Texture2DArray g_SplatDiffuse : register(t30);
Texture2DArray g_SplatNormal : register(t31);
Texture2DArray g_SplatAlpha : register(t32);

Texture2DArray g_SPLTexture : register(t34);
Texture2DArray g_SPLNormal : register(t35);

float3 BrushColor(float3 pos)
{
	if (B_Type == 1) // 원
	{
		float x = pos.x - B_Location.x;
		float z = pos.z - B_Location.z;
		float distance = sqrt(x * x + z * z);

		if (distance <= B_Range)
			return B_Color;
	}
	else if (B_Type == 2) // 사각형
	{
		float x = pos.x - B_Location.x;
		float z = pos.z - B_Location.z;
		float distX = abs(x);
		float distZ = abs(z);

		if (distX <= B_Range && distZ <= B_Range)
			return B_Color;
	}
	//
	return float3(0, 0, 0);
}

float3 ComputeSplatBumpNormal(Vertex3DSplattingOutput input, float2 UV)
{
	float3 result = input.Normal;
	
	if (g_MtrlBumpEnable == 1)
	{
		float4 NormalColor = g_NormalTexture.Sample(g_BaseSmp, UV);

		float4 SPLNormal;

		for (int Idx = 0; Idx < 12; ++Idx)
		{
			SPLNormal = g_SPLNormal.Sample(g_BaseSmp, float3(input.UV, Idx));

			if (Idx < 4)
				NormalColor = lerp(NormalColor, SPLNormal, input.SPLNormal[Idx]);

			else if (Idx < 8)
				NormalColor = lerp(NormalColor, SPLNormal, input.SPLNormal2[Idx - 4]);

			else if (Idx < 12)
				NormalColor = lerp(NormalColor, SPLNormal, input.SPLNormal3[Idx - 8]);
		}
		
		for (int i = 0; i < g_LandScapeSplatCount; ++i)
		{
			float4 SplatNormal = g_SplatNormal.Sample(g_BaseSmp, float3(UV, i));
			float4 SplatAlpha = g_SplatAlpha.Sample(g_BaseSmp, float3(input.UV, i));
		
			NormalColor.rgb = NormalColor.rgb * (1.f - SplatAlpha.r) + SplatNormal.rgb * SplatAlpha.r;
		}
		
		float3 ConvertNormal = NormalColor.xyz * 2.f - 1.f;

		ConvertNormal.z = 1.f;
		ConvertNormal = normalize(ConvertNormal);

		float3x3 mat =
		{
			input.Tangent,
			input.Binormal,
			input.Normal
		};

		result = normalize(mul(ConvertNormal, mat));
	}
	
	return result;
}


Vertex3DSplattingOutput LandScapeVS(Vertex3DSplatting input)
{
	Vertex3DSplattingOutput output = (Vertex3DSplattingOutput) 0;
	
	float3 Pos = input.Pos;

	output.ProjPos = mul(float4(Pos, 1.f), g_matWVP);
	output.Pos = output.ProjPos;
	
	output.ViewPos = mul(float4(Pos, 1.f), g_matWV).xyz;
	output.Normal = normalize(mul(float4(input.Normal, 0.f), g_matWV).xyz);
	output.Tangent = normalize(mul(float4(input.Tangent, 0.f), g_matWV).xyz);
	output.Binormal = normalize(mul(float4(input.Binormal, 0.f), g_matWV).xyz);
	output.UV = input.UV;

	output.SPLTexture = input.SPLTexture;
	output.SPLNormal = input.SPLNormal;
	output.SPLTexture2 = input.SPLTexture2;
	output.SPLNormal2 = input.SPLNormal2;
	output.SPLTexture3 = input.SPLTexture3;
	output.SPLNormal3 = input.SPLNormal3;

	return output;
}

PSOutput_GBuffer LandScapePS(Vertex3DSplattingOutput input)
{
	PSOutput_GBuffer output = (PSOutput_GBuffer) 0;
	
	float2 UV = input.UV * g_LandScapeDetailLevel;

	float4 BaseTextureColor = g_BaseTexture.Sample(g_BaseSmp, UV);

	float4 SPLTexture;

	for (int Idx = 0; Idx < 12; ++Idx)
	{
		SPLTexture = g_SPLTexture.Sample(g_BaseSmp, float3(input.UV, Idx));

		if (Idx < 4)
			BaseTextureColor = lerp(BaseTextureColor, SPLTexture, input.SPLTexture[Idx]);

		else if (Idx < 8)
			BaseTextureColor = lerp(BaseTextureColor, SPLTexture, input.SPLTexture2[Idx - 4]);

		else if (Idx < 12)
			BaseTextureColor = lerp(BaseTextureColor, SPLTexture, input.SPLTexture3[Idx - 8]);
	}
	
	for (int i = 0; i < g_LandScapeSplatCount; ++i)
	{
		float4 SplatDiffuse = g_SplatDiffuse.Sample(g_BaseSmp, float3(UV, i));		
		float4 SplatAlpha = g_SplatAlpha.Sample(g_BaseSmp, float3(input.UV, i));
		
		BaseTextureColor.rgb = BaseTextureColor.rgb * (1.f - SplatAlpha.r) + SplatDiffuse.rgb * SplatAlpha.r;
	}
	
	float3 WorldPos = mul(input.ProjPos, g_matInvVP).xyz;

	if (B_Type != 0)
	{
		float3 brushColor = BrushColor(WorldPos);

		output.Diffuse.rgb = BaseTextureColor.rgb + brushColor.rgb;
	}

	else
		output.Diffuse.rgb = BaseTextureColor.rgb;

	output.Diffuse.a = BaseTextureColor.a * g_MtrlOpacity;
	
	output.GBuffer1.rgb = ComputeSplatBumpNormal(input, UV);
	output.GBuffer1.a = 1.f;
	
	output.GBuffer2.r = input.ProjPos.z / input.ProjPos.w;
	output.GBuffer2.g = input.ProjPos.w;
	output.GBuffer2.b = 1.f;
	output.GBuffer2.a = 1.f;
	
	output.GBuffer3.r = ConvertColor(g_MtrlBaseColor);
	output.GBuffer3.g = ConvertColor(g_MtrlAmbientColor);
	
	output.GBuffer4.rgb = input.Tangent.xyz;
	output.GBuffer4.a = 1.f;
	
	output.GBuffer5.rgb = input.Binormal.xyz;
	output.GBuffer5.a = 1.f;
	
	float4 EmissiveColor = g_MtrlEmissiveColor.xyzw;
	
	if (g_MtrlEmissiveTex)
		EmissiveColor = g_EmissiveTexture.Sample(g_BaseSmp, UV).rgba;
	
	output.GBuffer3.a = ConvertColor(EmissiveColor);

	return output;

}
