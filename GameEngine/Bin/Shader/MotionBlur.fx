
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
	float3 Normal : NORMAL;
	float2 UV : TEXCOORD;
	float4 ProjPos : POSITION1;
	float4 Dir : POSITION2;
};

Vertex3DOutput VS(Vertex3D input)
{
	Vertex3DOutput output = (Vertex3DOutput)0;

	output.Pos = mul(float4(input.Pos, 1.f), g_matWVP);
	output.Normal = normalize(mul(vector(input.Normal, 0.f), g_matWV));
	output.UV = input.UV;
	
	float4 NewPos = output.Pos;
	float4 OldPos = mul(float4(input.Pos, 1.f), g_matPrevWorld);
	OldPos = mul(OldPos, g_matPrevView);
	OldPos = mul(OldPos, g_matProj);
	
	float3 Dir = NewPos.xyz - OldPos.xyz;
	
	float a = dot(normalize(Dir), normalize(output.Normal));
	
	if (a < 0.f)
	{
		output.Pos = OldPos;
	}
	
	else
	{
		output.Pos = NewPos;
	}
	
	float2 Velocity = (NewPos.xy / NewPos.w) - (OldPos.xy / OldPos.w);
	
	output.Dir.xy = Velocity * 0.5f;
	
	output.Dir.y *= -1.f;
	
	output.Dir.z = output.Pos.z;
	output.Dir.w = output.Pos.w;

	//float3 Pos = input.Pos;
	//
	//output.ProjPos = mul(float4(Pos, 1.f), g_matWVP);
	//output.Pos = output.ProjPos;

	return output;
}


PSOutput_Single PS(Vertex3DOutput input)
{
	PSOutput_Single output = (PSOutput_Single)0;

	output.Color.xy = input.Dir.xy;

	output.Color.z = 1.f;

	output.Color.w = input.Dir.z / input.Dir.w;
	
	return output;
}
