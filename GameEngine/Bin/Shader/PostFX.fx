
#include "ShaderInfo.fx"

Texture2DMS<float4> HDRTex		: register(t0);
StructuredBuffer<float> AvgLum	: register(t1);
Texture2D<float4> BloomTex : register(t2);	
Texture2D<float4> DOFBlurTex : register(t3);
Texture2DMS<float4> GBufferDepth : register(t10);

SamplerState PointSampler		: register(s0);
SamplerState LinearSmpler		: register(s1);

static const float2 arrBasePos[4] = {
	float2(-1.0, 1.0),
	float2(1.0, 1.0),
	float2(-1.0, -1.0),
	float2(1.0, -1.0),
};

static const float2 arrUV[4] = {
	float2(0.0, 0.0),
	float2(1.0, 0.0),
	float2(0.0, 1.0),
	float2(1.0, 1.0),
};

//-----------------------------------------------------------------------------------------
// Vertex shader
//-----------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Position : SV_Position; // vertex position 
	float4 ProjPos : POSITION;
	float2 UV		: TEXCOORD0;
};

VS_OUTPUT FullScreenQuadVS(uint VertexID : SV_VertexID)
{
	VS_OUTPUT Output;

	Output.Position = float4(arrBasePos[VertexID].xy, 0.0, 1.0);
	Output.ProjPos = float4(arrBasePos[VertexID], 0.f, 1.f);
	Output.UV = arrUV[VertexID].xy;

	return Output;
}

//-----------------------------------------------------------------------------------------
// Pixel shader
//-----------------------------------------------------------------------------------------

cbuffer FinalPassConstants : register(b0)
{
	// Tone mapping
	float	MiddleGrey : packoffset(c0);
	float	LumWhiteSqr : packoffset(c0.y);
	float	BloomScale : packoffset(c0.z);
	int		BlurEnable : packoffset(c0.w);
	float2  ProjectionValue: packoffset(c1);
	float2  DOFFarValue: packoffset(c1.z);
}

static const float3 LUM_FACTOR = float3(0.299, 0.587, 0.114);

float ConvertZToLinearDepth(float Depth)
{
	// x -> -0.1f , y -> -1.f
	float LinearDepth = ProjectionValue.x / (Depth + ProjectionValue.y);

	return LinearDepth;
}

float3 DistanceDOF(float3 ColorFocus, float3 ColorBlurred, float Depth)
{
	// Find the depth based blur factor
	float BlurFactor = 0.f;

	if (BlurEnable)
		BlurFactor = 0.8f;

	else
	{
		float FarValueY = 1.f / DOFFarValue.y;
		float StartDepth = Depth - DOFFarValue.x;

		if (StartDepth > 0.f)
		{
			BlurFactor = saturate((Depth - DOFFarValue.x) * FarValueY);
		}

		else
		{
			StartDepth *= -1.f;
			BlurFactor = saturate(StartDepth / DOFFarValue.x);
		}
	}

	// Lerp with the blurred color based on the CoC factor
	return lerp(ColorFocus, ColorBlurred, BlurFactor);
}

float3 ToneMapping(float3 HDRColor)
{
	// Find the luminance scale for the current pixel
	float LScale = dot(HDRColor, LUM_FACTOR);
	LScale *= MiddleGrey / AvgLum[0];
	LScale = (LScale + LScale * LScale / LumWhiteSqr) / (1.0 + LScale);

	// Apply the luminance scale to the pixels color
	return HDRColor * LScale;
}

float4 FinalPassPS(VS_OUTPUT In) : SV_TARGET
{
	float2 UV;
	UV.x = In.ProjPos.x / In.ProjPos.w * 0.5f + 0.5f;
	UV.y = In.ProjPos.y / In.ProjPos.w * -0.5f + 0.5f;

	int2 TargetPos = (int2) 0;

	TargetPos.x = (int)(UV.x * g_Resolution.x);
	TargetPos.y = (int)(UV.y * g_Resolution.y);

	// Get the color sample
	float3 color = HDRTex.Load(TargetPos, 0).xyz;

	// Distance DOF only on pixels that are not on the far plane
	float Depth = GBufferDepth.Load(TargetPos, 0).r;
	float G = GBufferDepth.Load(TargetPos, 0).g;
	Depth *= G;

	float3 colorBlurred = DOFBlurTex.Sample(LinearSmpler, In.UV.xy).xyz;

	color = DistanceDOF(color, colorBlurred, Depth);
	
	color += BloomScale * BloomTex.Sample(LinearSmpler, In.UV.xy).xyz;

	// Tone mapping
	color = ToneMapping(color);

	// Output the LDR value
	return float4(color, 1.0);
}