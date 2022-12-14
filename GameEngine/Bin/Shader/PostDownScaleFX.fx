//-----------------------------------------------------------------------------------------
// Compute shader
//-----------------------------------------------------------------------------------------
Texture2DMS<float4> HDRTex : register(t0);
StructuredBuffer<float> AverageValues1D : register(t1);
StructuredBuffer<float> PrevAvgLum : register(t2);

RWStructuredBuffer<float> AverageLum : register(u0);

//For bloom
RWTexture2D<float4> HDRDownScale: register(u1);

cbuffer DownScaleConstants : register(b0)
{
	uint2 Res		 : packoffset(c0);   // Resulotion of the qurter size target: x - width, y - height
	uint Domain		 : packoffset(c0.z); // Total pixel in the downscaled image
	uint GroupSize	 : packoffset(c0.w); // Number of groups dispached on the first pass
	float Adaptation : packoffset(c1);   // Adaptation factor
	float  BloomThreshold : packoffset(c1.y); // Bloom 효과 적용할 임계값 비율
}

// Group shared memory to store the intermidiate results
groupshared float SharedPositions[1024];

static const float4 LUM_FACTOR = float4(0.299, 0.587, 0.114, 0);

//float DownScale4x4(uint2 CurPixel, uint groupThreadId)
//{
//	float avgLum = 0.0;
//
//	// Skip out of bound pixels
//	if (CurPixel.y < Res.y)
//	{
//		// Sum a group of 4x4 pixels
//		int3 nFullResPos = int3(CurPixel * 4, 0);
//		float4 downScaled = float4(0.0, 0.0, 0.0, 0.0);
//		[unroll]
//		for (int i = 0; i < 4; i++)
//		{
//			[unroll]
//			for (int j = 0; j < 4; j++)
//			{
//				downScaled += HDRTex.Load(nFullResPos, int2(j, i));
//			}
//		}
//		downScaled /= 16.0;
//
//		// downScaled 값을 새 UAV에 저장.
//		HDRDownScale[CurPixel.xy] = downScaled;
//
//		// Calculate the lumenace value for this pixel
//		avgLum = dot(downScaled, LUM_FACTOR);
//
//
//		// Write the result to the shared memory
//		SharedPositions[groupThreadId] = avgLum;
//	}
//
//	// Synchronize before next step
//	GroupMemoryBarrierWithGroupSync();
//
//	return avgLum;
//}
//
//float DownScale1024to4(uint dispatchThreadId, uint groupThreadId, float avgLum)
//{
//	// Expend the downscale code from a loop
//	[unroll]
//	for (uint groupSize = 4, step1 = 1, step2 = 2, step3 = 3; groupSize < 1024; groupSize *= 4, step1 *= 4, step2 *= 4, step3 *= 4)
//	{
//		// Skip out of bound pixels
//		if (groupThreadId % groupSize == 0)
//		{
//			// Calculate the luminance sum for this step
//			float stepAvgLum = avgLum;
//			stepAvgLum += dispatchThreadId + step1 < Domain ? SharedPositions[groupThreadId + step1] : avgLum;
//			stepAvgLum += dispatchThreadId + step2 < Domain ? SharedPositions[groupThreadId + step2] : avgLum;
//			stepAvgLum += dispatchThreadId + step3 < Domain ? SharedPositions[groupThreadId + step3] : avgLum;
//
//			// Store the results
//			avgLum = stepAvgLum;
//			SharedPositions[groupThreadId] = stepAvgLum;
//		}
//
//		// Synchronize before next step
//		GroupMemoryBarrierWithGroupSync();
//	}
//
//	return avgLum;
//}
//
//void DownScale4to1(uint dispatchThreadId, uint groupThreadId, uint groupId, float avgLum)
//{
//	if (groupThreadId == 0)
//	{
//		// Calculate the average lumenance for this thread group
//		float fFinalAvgLum = avgLum;
//		fFinalAvgLum += dispatchThreadId + 256 < Domain ? SharedPositions[groupThreadId + 256] : avgLum;
//		fFinalAvgLum += dispatchThreadId + 512 < Domain ? SharedPositions[groupThreadId + 512] : avgLum;
//		fFinalAvgLum += dispatchThreadId + 768 < Domain ? SharedPositions[groupThreadId + 768] : avgLum;
//		fFinalAvgLum /= 1024.0;
//
//		// Write the final value into the 1D UAV which will be used on the next step
//		AverageLum[groupId] = fFinalAvgLum;
//	}
//}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Second pass - convert the 1D average values into a single value
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_GROUPS 64

// Group shared memory to store the intermidiate results
groupshared float SharedAvgFinal[MAX_GROUPS];

[numthreads(1024, 1, 1)]
void DownScaleFirstPass(uint3 dispatchThreadId : SV_DispatchThreadID, uint3 groupThreadId : SV_GroupThreadID, uint3 groupId : SV_GroupID)
{
	uint2 CurPixel = uint2(dispatchThreadId.x % Res.x, dispatchThreadId.x / Res.x);

	// Skip out of bound pixels
	float avgLum = 0.0;
	if (CurPixel.y < Res.y)
	{
		int3 nFullResPos = int3(CurPixel * 4, 0);
		float4 downScaled = float4(0.0, 0.0, 0.0, 0.0);
		[unroll]
		for (int i = 0; i < 4; i++)
		{
			[unroll]
			for (int j = 0; j < 4; j++)
			{
				downScaled += HDRTex.Load(nFullResPos.xy, i * 4 + j);
			}
		}
		downScaled /= 4.0; // Average

		HDRDownScale[CurPixel.xy] = downScaled;

		avgLum = dot(downScaled, LUM_FACTOR); // Calculate the lumenace value for this pixel
	}
	SharedPositions[groupThreadId.x] = avgLum; // Store in the group memory for further reduction

	GroupMemoryBarrierWithGroupSync(); // Sync before next step

	// Down scale from 1024 to 256
	if (groupThreadId.x % 4 == 0)
	{
		// Calculate the luminance sum for this step
		float stepAvgLum = avgLum;
		stepAvgLum += dispatchThreadId.x + 1 < Domain ? SharedPositions[groupThreadId.x + 1] : avgLum;
		stepAvgLum += dispatchThreadId.x + 2 < Domain ? SharedPositions[groupThreadId.x + 2] : avgLum;
		stepAvgLum += dispatchThreadId.x + 3 < Domain ? SharedPositions[groupThreadId.x + 3] : avgLum;

		// Store the results
		avgLum = stepAvgLum;
		SharedPositions[groupThreadId.x] = stepAvgLum;
	}

	GroupMemoryBarrierWithGroupSync(); // Sync before next step

	// Downscale from 256 to 64
	if (groupThreadId.x % 16 == 0)
	{
		// Calculate the luminance sum for this step
		float stepAvgLum = avgLum;
		stepAvgLum += dispatchThreadId.x + 4 < Domain ? SharedPositions[groupThreadId.x + 4] : avgLum;
		stepAvgLum += dispatchThreadId.x + 8 < Domain ? SharedPositions[groupThreadId.x + 8] : avgLum;
		stepAvgLum += dispatchThreadId.x + 12 < Domain ? SharedPositions[groupThreadId.x + 12] : avgLum;

		// Store the results
		avgLum = stepAvgLum;
		SharedPositions[groupThreadId.x] = stepAvgLum;
	}

	GroupMemoryBarrierWithGroupSync(); // Sync before next step

	// Downscale from 64 to 16
	if (groupThreadId.x % 64 == 0)
	{
		// Calculate the luminance sum for this step
		float stepAvgLum = avgLum;
		stepAvgLum += dispatchThreadId.x + 16 < Domain ? SharedPositions[groupThreadId.x + 16] : avgLum;
		stepAvgLum += dispatchThreadId.x + 32 < Domain ? SharedPositions[groupThreadId.x + 32] : avgLum;
		stepAvgLum += dispatchThreadId.x + 48 < Domain ? SharedPositions[groupThreadId.x + 48] : avgLum;

		// Store the results
		avgLum = stepAvgLum;
		SharedPositions[groupThreadId.x] = stepAvgLum;
	}

	GroupMemoryBarrierWithGroupSync(); // Sync before next step

	// Downscale from 16 to 4
	if (groupThreadId.x % 256 == 0)
	{
		// Calculate the luminance sum for this step
		float stepAvgLum = avgLum;
		stepAvgLum += dispatchThreadId.x + 64 < Domain ? SharedPositions[groupThreadId.x + 64] : avgLum;
		stepAvgLum += dispatchThreadId.x + 128 < Domain ? SharedPositions[groupThreadId.x + 128] : avgLum;
		stepAvgLum += dispatchThreadId.x + 192 < Domain ? SharedPositions[groupThreadId.x + 192] : avgLum;

		// Store the results
		avgLum = stepAvgLum;
		SharedPositions[groupThreadId.x] = stepAvgLum;
	}

	GroupMemoryBarrierWithGroupSync(); // Sync before next step

	// Downscale from 4 to 1
	if (groupThreadId.x == 0)
	{
		// Calculate the average lumenance for this thread group
		float fFinalAvgLum = avgLum;
		fFinalAvgLum += dispatchThreadId.x + 256 < Domain ? SharedPositions[groupThreadId.x + 256] : avgLum;
		fFinalAvgLum += dispatchThreadId.x + 512 < Domain ? SharedPositions[groupThreadId.x + 512] : avgLum;
		fFinalAvgLum += dispatchThreadId.x + 768 < Domain ? SharedPositions[groupThreadId.x + 768] : avgLum;
		fFinalAvgLum /= 1024.0;

		AverageLum[groupId.x] = fFinalAvgLum; // Write the final value into the 1D UAV which will be used on the next step
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Second pass - convert the 1D average values into a single value
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



[numthreads(MAX_GROUPS, 1, 1)]
void DownScaleSecondPass(uint3 groupId : SV_GroupID, uint3 groupThreadId : SV_GroupThreadID,
	uint3 dispatchThreadId : SV_DispatchThreadID, uint groupIndex : SV_GroupIndex)
{
	// Fill the shared memory with the 1D values
	float avgLum = 0.0;
	if (dispatchThreadId.x < GroupSize)
	{
		avgLum = AverageValues1D[dispatchThreadId.x];
	}
	SharedAvgFinal[dispatchThreadId.x] = avgLum;

	GroupMemoryBarrierWithGroupSync(); // Sync before next step

	// Downscale from 64 to 16
	if (dispatchThreadId.x % 4 == 0)
	{
		// Calculate the luminance sum for this step
		float stepAvgLum = avgLum;
		stepAvgLum += dispatchThreadId.x + 1 < GroupSize ? SharedAvgFinal[dispatchThreadId.x + 1] : avgLum;
		stepAvgLum += dispatchThreadId.x + 2 < GroupSize ? SharedAvgFinal[dispatchThreadId.x + 2] : avgLum;
		stepAvgLum += dispatchThreadId.x + 3 < GroupSize ? SharedAvgFinal[dispatchThreadId.x + 3] : avgLum;

		// Store the results
		avgLum = stepAvgLum;
		SharedAvgFinal[dispatchThreadId.x] = stepAvgLum;
	}

	GroupMemoryBarrierWithGroupSync(); // Sync before next step

	// Downscale from 16 to 4
	if (dispatchThreadId.x % 16 == 0)
	{
		// Calculate the luminance sum for this step
		float stepAvgLum = avgLum;
		stepAvgLum += dispatchThreadId.x + 4 < GroupSize ? SharedAvgFinal[dispatchThreadId.x + 4] : avgLum;
		stepAvgLum += dispatchThreadId.x + 8 < GroupSize ? SharedAvgFinal[dispatchThreadId.x + 8] : avgLum;
		stepAvgLum += dispatchThreadId.x + 12 < GroupSize ? SharedAvgFinal[dispatchThreadId.x + 12] : avgLum;

		// Store the results
		avgLum = stepAvgLum;
		SharedAvgFinal[dispatchThreadId.x] = stepAvgLum;
	}

	GroupMemoryBarrierWithGroupSync(); // Sync before next step

	// Downscale from 4 to 1
	if (dispatchThreadId.x == 0)
	{
		// Calculate the average luminace
		float fFinalLumValue = avgLum;
		fFinalLumValue += dispatchThreadId.x + 16 < GroupSize ? SharedAvgFinal[dispatchThreadId.x + 16] : avgLum;
		fFinalLumValue += dispatchThreadId.x + 32 < GroupSize ? SharedAvgFinal[dispatchThreadId.x + 32] : avgLum;
		fFinalLumValue += dispatchThreadId.x + 48 < GroupSize ? SharedAvgFinal[dispatchThreadId.x + 48] : avgLum;
		fFinalLumValue /= 64.0;

		// Calculate the adaptive luminance
		float fAdaptedAverageLum = lerp(PrevAvgLum[0], fFinalLumValue, Adaptation);

		// Store the final value
		AverageLum[0] = max(fAdaptedAverageLum, 0.0001);
	}
}


//For bloom
Texture2D<float4> HDRDownScaleTex : register(t0);
StructuredBuffer<float> AvgLum: register(t1);
RWTexture2D<float4> Bloom: register(u0);
RWTexture2D<float4> Blur: register(u1);

[numthreads(1024, 1, 1)]
void BloomReveal(uint3 dispatchThreadId : SV_DispatchThreadID)
{
	uint2 CurPixel = uint2(dispatchThreadId.x % Res.x, dispatchThreadId.x / Res.x);

	// Skip out of bound pixels
	if (CurPixel.y < Res.y)
	{
		float4 color = HDRDownScaleTex.Load(int3(CurPixel, 0));
		float Lum = dot(color, LUM_FACTOR);
		float avgLum = AvgLum[0];

		// Find the color scale
		float colorScale = saturate(Lum - avgLum * BloomThreshold);

		Blur[CurPixel.xy] = color;
		Bloom[CurPixel.xy] = color * colorScale;
	}
}

