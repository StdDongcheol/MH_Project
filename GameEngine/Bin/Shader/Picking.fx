
cbuffer PickingCBuffer : register(b13)
{
	float3	Pos;
	uint	OutputSize;
	float3	Dir;
	int		Empty;
}

struct PickingInputDesc
{
	uint	Index;
	float3	V0;
	float3	V1;
	float3	V2;
};
StructuredBuffer<PickingInputDesc> Input : register(t25);

struct PickingOutputDesc
{
	int		Picked;
	float2	UV;
	float	Dist;
};
RWStructuredBuffer<PickingOutputDesc> Output : register(u5);

void Intersect(uint Index)
{
	float3 A = Input[Index].V0;
	float3 B = Input[Index].V1;
	float3 C = Input[Index].V2;

	float3 E1 = B - A;
	float3 E2 = C - A;

	float3 P, T, Q;
	P = cross(Dir, E2);

	float d = 1.f / dot(E1, P);

	T = Pos - A;
	Output[Index].UV.x = dot(T, P) * d;

	Q = cross(T, E1);
	Output[Index].UV.y = dot(Dir, Q) * d;
	Output[Index].Dist = dot(E2, Q) * d;

	bool b = (Output[Index].UV.x >= 0.f) &&
		(Output[Index].UV.y >= 0.f) &&
		(Output[Index].UV.x + Output[Index].UV.y <= 1.f) &&
		(Output[Index].Dist >= 0.f);

	Output[Index].Picked = b ? 1 : 0;
}

[numthreads(32, 32, 1)]
void PickingCS(uint3 ThreadID : SV_GroupID, uint groupIndex : SV_GroupIndex)
{
	uint Index = ThreadID.x * 32 * 32 + groupIndex;

	if (OutputSize > Index)
		Intersect(Index);
}