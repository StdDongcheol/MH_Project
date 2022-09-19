
#include "ShaderInfo.fx"


struct Vertex3D
{
    // ���� �ڿ� : ���������̸� + ��ȣ �� �����Ѵ�.
    // ��ȣ�� �Ⱥ��̸� 0���� �����ȴ�.
    float3 Pos : POSITION; // Vector3Ÿ��.
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
    float4 BlendWeight : BLENDWEIGHT;
    float4 BlendIndex : BLENDINDEX;
};

struct Vertex3DOutput
{
    // SV�� ������ System Value�̴�. �� ���� �������Ϳ� ���常 �ϰ�
    // ������ ����ϸ� �ȵȴ�.
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
    float4 ProjPos : POSITION;
    float3 ViewPos : POSITION1;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
    float2	OriginUV : TEXCOORD1;
    float3 WorldNormal : NORMAL1;
};

cbuffer RimLightCBuffer : register(b13)
{
    int g_RimLightEnable;
    float3 g_RimCameraPos;
    float3 g_RimColor;
    float  g_RimPower;
    float3 g_RimEmissiveColor;
    float  g_RimEmpty;
}

Texture2DMS<float4> g_RimSpecTex : register(t25);

StructuredBuffer<matrix> g_SkinningBoneMatrixArray : register(t106);

struct SkinningInfo
{
    float3 Pos;
    float3 Normal;
    float3 Tangent;
    float3 Binormal;
};

SkinningInfo Skinning(float3 Pos, float3 Normal, float3 Tangent, float3 Binormal,
    float4 BlendWeight, float4 BlendIndex)
{
    SkinningInfo Info = (SkinningInfo)0;

    if (g_MtrlAnimation3DEnable == 0)
    {
        Info.Pos = Pos;
        Info.Normal = Normal;
        Info.Tangent = Tangent;
        Info.Binormal = Binormal;

        return Info;
    }

    for (int i = 0; i < 4; ++i)
    {
        if (BlendWeight[i] == 0.f)
            continue;

        matrix matBone = g_SkinningBoneMatrixArray[(int)BlendIndex[i]];

        Info.Pos += (mul(float4(Pos, 1.f), matBone) * BlendWeight[i]).xyz;
        Info.Normal += (mul(float4(Normal, 0.f), matBone) * BlendWeight[i]).xyz;
        Info.Tangent += (mul(float4(Tangent, 0.f), matBone) * BlendWeight[i]).xyz;
        Info.Binormal += (mul(float4(Binormal, 0.f), matBone) * BlendWeight[i]).xyz;
    }

    Info.Normal = normalize(Info.Normal);
    Info.Tangent = normalize(Info.Tangent);
    Info.Binormal = normalize(Info.Binormal);

    return Info;
}

Vertex3DOutput RimLightVS(Vertex3D input)
{
    Vertex3DOutput output = (Vertex3DOutput)0;

    SkinningInfo Info = Skinning(input.Pos, input.Normal, input.Tangent,
        input.Binormal, input.BlendWeight, input.BlendIndex);

    float3 Pos = Info.Pos;

    output.ProjPos = mul(float4(Pos, 1.f), g_matWVP);
    output.Pos = output.ProjPos;

    // ������� ��ġ�� ������ش�.
    output.ViewPos = mul(float4(input.Pos, 1.f), g_matWV).xyz;

    // �� ������ Normal�� ������ش�.
    output.Normal = normalize(mul(float4(Info.Normal, 0.f), g_matWV).xyz);
    // �� ������ Tangent�� ������ش�.
    output.Tangent = normalize(mul(float4(Info.Tangent, 0.f), g_matWV).xyz);
    // �� ������ Binormal�� ������ش�.
    output.Binormal = normalize(mul(float4(Info.Binormal, 0.f), g_matWV).xyz);
    output.UV = input.UV;
    output.OriginUV = input.UV;
    output.WorldNormal = normalize(mul(float4(input.Normal, 0.f), g_matWorld).xyz);

    return output;
}

PSOutput_GBuffer RimLightPS(Vertex3DOutput input)
{
    PSOutput_GBuffer output = (PSOutput_GBuffer)0;

    float4 BaseTextureColor = g_BaseTexture.Sample(g_BaseSmp, input.UV);

    if (BaseTextureColor.a == 0.f || g_MtrlOpacity == 0.f)
        clip(-1);

    float3 RimColor = float3(0.f, 0.f, 0.f);// g_RimColor;

    float4 EmissiveColor = g_MtrlEmissiveColor.xyzw;

    RimColor = g_RimColor;//float3(1.f, 0.f, 0.f);

    float3 ViewCameraPos = mul(float4(g_RimCameraPos, 1.f), g_matView).xyz;

    // ViewDir : ���ؽ����� �ٶ󺸴� ī�޶��� ����
    float3 ViewDir = normalize(ViewCameraPos - input.ViewPos);

    float Rim = saturate(dot(input.Normal, ViewDir));


    if (g_MtrlEmissiveTex)
        EmissiveColor = g_EmissiveTexture.Sample(g_BaseSmp, input.UV).xxxx;

    if (g_RimLightEnable)
    {
        EmissiveColor = float4(pow(1 - Rim, g_RimPower) * RimColor, 1.f) + float4(g_RimEmissiveColor, 0.f);
    }

    if (g_RimLightEnable)
    {
        output.Diffuse.rgb = BaseTextureColor.rgb;// *RimColor;// +g_RimColor;// * (LightInfo.Dif + LightInfo.Amb) + LightInfo.Spc + LightInfo.Emv;
    }

    else
    {
        output.Diffuse.rgb = BaseTextureColor.rgb;
    }

    output.Diffuse.a = BaseTextureColor.a * g_MtrlOpacity; 

    output.GBuffer1.rgb = ComputeBumpNormal(input.Normal, input.Tangent, input.Binormal, input.UV);
    output.GBuffer1.a = 1.f;

    output.GBuffer2.r = input.ProjPos.z / input.ProjPos.w;
    output.GBuffer2.g = input.ProjPos.w;
    output.GBuffer2.b = g_MtrlSpecularColor.w;
    output.GBuffer2.a = 1.f;

    output.GBuffer3.r = ConvertColor(g_MtrlBaseColor);
    output.GBuffer3.g = ConvertColor(g_MtrlAmbientColor);

    output.GBuffer4.rgb = input.Tangent.xyz;
    output.GBuffer4.a = g_MtrlReceiveDecal;

    output.GBuffer5.rgb = input.Binormal.xyz;
    output.GBuffer5.a = 1.f;

    /*float4 SpecularColor = g_MtrlSpecularColor.xyzw;

    if (g_MtrlSpecularTex)
        SpecularColor = g_SpecularTexture.Sample(g_BaseSmp, input.UV).xxxx;*/

    //SpecularColor = float4(0.5f, 0.5f, 0.5f, 1.f);

    float4 SpecularColor = g_MtrlSpecularColor.xyzw;

    if (g_MtrlSpecularTex)
        SpecularColor = g_SpecularTexture.Sample(g_BaseSmp, input.UV).xxxx;
 
    if (g_RimLightEnable)
        SpecularColor = SpecularColor;

    //SpecularColor = float4(1.f, 0.f, 0.f, 0.f);


    output.GBuffer3.b = ConvertColor(SpecularColor);

    /*float4 EmissiveColor = g_MtrlEmissiveColor.xyzw;

    if (g_MtrlEmissiveTex)
        EmissiveColor = g_EmissiveTexture.Sample(g_BaseSmp, input.UV).xxxx;

    if (g_RimLightEnable)
    {
        EmissiveColor = EmissiveColor + float4(rimColor, 1.f);
    }*/

    output.GBuffer3.a = ConvertColor(EmissiveColor);

    return output;
}