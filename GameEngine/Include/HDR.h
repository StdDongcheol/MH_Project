#pragma once
#include "GameInfo.h"
class CHDR
{
private:
	bool EnableHDR;
	bool IsWindowOn;
public:
	bool Init(UINT width, UINT height);
	void Deinit();

	void PostProcessing(ID3D11DeviceContext* pd3dImmediateContext, ID3D11ShaderResourceView* pHDRSRV, ID3D11RenderTargetView* pLDRRTV);

	void SetParameters(float fMiddleGrey, float fWhite) { m_fMiddleGrey = fMiddleGrey; m_fWhite = fWhite; }

	void SetIsWindowOn(bool b)
	{
		IsWindowOn = b;
	}

	void SetGrey(float grey)
	{
		m_fMiddleGrey = grey;
	}

	void SetWhite(float white)
	{
		m_fWhite = white;
	}

	void SetBloomScale(float BloomScale)
	{
		m_fBloomScale = BloomScale;
	}

	void SetBloomThreshold(float BloomThreshold)
	{
		m_fBloomThreshold = BloomThreshold;
	}

	void SetNearStart(float NearStart)
	{
		m_fNearStart = NearStart;
	}

	void SetFarStart(float FarStart)
	{
		m_fFarStart = FarStart;
	}
	/////////////////////////

	bool GetIsWindowOn()
	{
		return IsWindowOn;
	}

	float GetGrey()
	{
		return m_fMiddleGrey;
	}

	float GetWhite()
	{
		return m_fWhite;
	}

	float GetBloomScale()
	{
		return m_fBloomScale;
	}

	float GetBloomThreshold()
	{
		return m_fBloomThreshold;
	}

	float GetNearStart()
	{
		return m_fNearStart;
	}

	float GetFarStart()
	{
		return m_fFarStart;
	}

	void CleanUp(ID3D11DeviceContext* pd3dImmediateContext);

public:
	void SetHDREnable(bool b)
	{
		EnableHDR = b;
	}

	bool GetHDREnable()
	{
		return EnableHDR;
	}

	void SetBlurEnable(bool Enable)
	{
		m_iEnableBlur = Enable ? 1 : 0;
	}


private:
	void DownScale(ID3D11DeviceContext* pd3dImmediateContext, ID3D11ShaderResourceView* pHDRSRV);

	// Final pass that composites all the post processing calculations
	void FinalPass(ID3D11DeviceContext* pd3dImmediateContext, ID3D11ShaderResourceView* pHDRSRV);

	void Bloom(ID3D11DeviceContext* pd3dImmediateContext);

	void Blur(ID3D11DeviceContext* pd3dImmediateContext, ID3D11ShaderResourceView* pInput, ID3D11UnorderedAccessView* pOutput);

	// 1D intermediate storage for the down scale operation
	ID3D11Buffer* m_pDownScale1DBuffer;
	ID3D11UnorderedAccessView* m_pDownScale1DUAV;
	ID3D11ShaderResourceView* m_pDownScale1DSRV;

	// Average luminance
	ID3D11Buffer* m_pAvgLumBuffer;
	ID3D11UnorderedAccessView* m_pAvgLumUAV;
	ID3D11ShaderResourceView* m_pAvgLumSRV;


	// Previous average luminance for adaptation
	ID3D11Buffer* m_pPrevAvgLumBuffer;
	ID3D11UnorderedAccessView* m_pPrevAvgLumUAV;
	ID3D11ShaderResourceView* m_pPrevAvgLumSRV;



	// DownScaled (For Bloom)
	ID3D11Texture2D* m_pDownScaleRT;
	ID3D11ShaderResourceView* m_pDownScaleSRV;		// Down Scaled SRV
	ID3D11UnorderedAccessView* m_pDownScaleUAV;		// Down Scaled UAV

	// Temporary texture
	ID3D11Texture2D* m_pTempRT[3];
	ID3D11ShaderResourceView* m_pTempSRV[3];
	ID3D11UnorderedAccessView* m_pTempUAV[3];

	// Bloom texture
	ID3D11Texture2D* m_pBloomRT;
	ID3D11ShaderResourceView* m_pBloomSRV;
	ID3D11UnorderedAccessView* m_pBloomUAV;

	// Blurs texture
	ID3D11Texture2D* m_pVerticalBlurRT;
	ID3D11ShaderResourceView* m_pVerticalBlurSRV;
	ID3D11UnorderedAccessView* m_pVerticalBlurUAV;


	UINT m_nWidth;
	UINT m_nHeight;
	UINT m_nDownScaleGroups;
	float m_fMiddleGrey;
	float m_fWhite;
	float m_fAdaptation;
	int	  m_iEnableBlur;


	float m_fBloomThreshold;
	float m_fBloomScale;

	float m_fNearStart;
	float m_fFarStart;


	ID3D11Buffer* m_pDownScaleCB;
	ID3D11Buffer* m_pFinalPassCB;

	// Shaders
	ID3D11ComputeShader* m_pDownScaleFirstPassCS;
	ID3D11ComputeShader* m_pDownScaleSecondPassCS;
	ID3D11ComputeShader* m_pBloomRevealCS;
	ID3D11ComputeShader* m_pVerticalBlurCS;
	ID3D11ComputeShader* m_pHorizontalBlurCS;
	ID3D11VertexShader* m_pFullScreenQuadVS;
	ID3D11PixelShader* m_pFinalPassPS;

	//sampler
	ID3D11SamplerState* SampPoint;
	ID3D11SamplerState* SampLinear;

public:
	DECLARE_SINGLE(CHDR)
};

