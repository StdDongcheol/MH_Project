#include "HDR.h"
#include "Device.h"
#include "PathManager.h"


DEFINITION_SINGLE(CHDR)

//m_fFarStart MAX -> 400.0f
//m_fFarRange MAX -> 150.0f
CHDR::CHDR() : m_fMiddleGrey(20.0025f), m_fWhite(20.5f), m_fAdaptation(5.0f), m_fBloomThreshold(-0.5f), m_fBloomScale(-0.4f),
	m_fNearStart(50.f), m_fFarStart(800.f),
	m_pDownScale1DBuffer(NULL), m_pDownScale1DUAV(NULL), m_pDownScale1DSRV(NULL),
	m_pDownScaleCB(NULL), m_pFinalPassCB(NULL),
	m_pAvgLumBuffer(NULL), m_pAvgLumUAV(NULL), m_pAvgLumSRV(NULL),
	m_pPrevAvgLumBuffer(NULL), m_pPrevAvgLumUAV(NULL), m_pPrevAvgLumSRV(NULL),
	m_pDownScaleFirstPassCS(NULL), m_pDownScaleSecondPassCS(NULL), m_pFullScreenQuadVS(NULL), m_pFinalPassPS(NULL), EnableHDR(true),
	m_iEnableBlur(0)
{
}//threshhold -4~4 scale 0~1 near 0~50, far 0~200

CHDR::~CHDR()
{
	SAFE_RELEASE(m_pDownScaleRT);
	SAFE_RELEASE(m_pDownScaleSRV);
	SAFE_RELEASE(m_pDownScaleUAV);
	SAFE_RELEASE(m_pTempRT[0]);
	SAFE_RELEASE(m_pTempSRV[0]);
	SAFE_RELEASE(m_pTempUAV[0]);
	SAFE_RELEASE(m_pTempRT[1]);
	SAFE_RELEASE(m_pTempSRV[1]);
	SAFE_RELEASE(m_pTempUAV[1]);
	SAFE_RELEASE(m_pTempRT[2]);
	SAFE_RELEASE(m_pTempSRV[2]);
	SAFE_RELEASE(m_pTempUAV[2]);
	SAFE_RELEASE(m_pBloomRT);
	SAFE_RELEASE(m_pBloomSRV);
	SAFE_RELEASE(m_pBloomUAV);
	SAFE_RELEASE(m_pVerticalBlurRT);
	SAFE_RELEASE(m_pVerticalBlurSRV);
	SAFE_RELEASE(m_pVerticalBlurUAV);
	SAFE_RELEASE(m_pBloomRevealCS);
	SAFE_RELEASE(m_pVerticalBlurCS);
	SAFE_RELEASE(m_pHorizontalBlurCS);
	SAFE_RELEASE(m_pDownScale1DBuffer);
	SAFE_RELEASE(m_pDownScale1DUAV);
	SAFE_RELEASE(m_pDownScale1DSRV);
	SAFE_RELEASE(m_pDownScaleCB);
	SAFE_RELEASE(m_pFinalPassCB);
	SAFE_RELEASE(m_pAvgLumBuffer);
	SAFE_RELEASE(m_pAvgLumUAV);
	SAFE_RELEASE(m_pAvgLumSRV);
	SAFE_RELEASE(m_pDownScaleFirstPassCS);
	SAFE_RELEASE(m_pDownScaleSecondPassCS);
	SAFE_RELEASE(m_pFullScreenQuadVS);
	SAFE_RELEASE(m_pFinalPassPS);
	SAFE_RELEASE(SampPoint);
	SAFE_RELEASE(SampLinear);
	SAFE_RELEASE(m_pPrevAvgLumBuffer);
	SAFE_RELEASE(m_pPrevAvgLumUAV);
	SAFE_RELEASE(m_pPrevAvgLumSRV);

}

bool CHDR::Init(UINT width, UINT height)
{
	Deinit();



	// Find the amount of thread groups needed for the downscale operation
	m_nWidth = width;
	m_nHeight = height;
	m_nDownScaleGroups = (UINT)ceil((float)(m_nWidth * m_nHeight / 16) / 1024.0f);

	//sampledesc
	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.MaxAnisotropy = 1;
	samDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samDesc.MaxLOD = D3D11_FLOAT32_MAX;


	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	CDevice::GetInst()->GetDevice()->CreateSamplerState(&samDesc, &SampPoint);

	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	CDevice::GetInst()->GetDevice()->CreateSamplerState(&samDesc, &SampLinear);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Allocate the downscaled target
	D3D11_TEXTURE2D_DESC dtd = {
		m_nWidth / 4, //UINT Width;
		m_nHeight / 4, //UINT Height;
		1, //UINT MipLevels;
		1, //UINT ArraySize;
		DXGI_FORMAT_R16G16B16A16_TYPELESS, //DXGI_FORMAT Format;
		1, //DXGI_SAMPLE_DESC SampleDesc;
		0,
		D3D11_USAGE_DEFAULT,//D3D11_USAGE Usage;
		D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS,//UINT BindFlags;
		0,//UINT CPUAccessFlags;
		0 //UINT MiscFlags;    
	};

	CDevice::GetInst()->GetDevice()->CreateTexture2D(&dtd, NULL, &m_pDownScaleRT);

	// Create the resource views
	D3D11_SHADER_RESOURCE_VIEW_DESC DownScaleDsrvd;
	ZeroMemory(&DownScaleDsrvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	DownScaleDsrvd.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	DownScaleDsrvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	DownScaleDsrvd.Texture2D.MipLevels = 1;
	CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_pDownScaleRT, &DownScaleDsrvd, &m_pDownScaleSRV);

	// Create the UAVs
	D3D11_UNORDERED_ACCESS_VIEW_DESC DescDownScaleUAV;
	ZeroMemory(&DescDownScaleUAV, sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
	DescDownScaleUAV.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	DescDownScaleUAV.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	DescDownScaleUAV.Buffer.FirstElement = 0;
	DescDownScaleUAV.Buffer.NumElements = m_nWidth * m_nHeight / 16;
	CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_pDownScaleRT, &DescDownScaleUAV, &m_pDownScaleUAV);


	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Allocate temporary target
	CDevice::GetInst()->GetDevice()->CreateTexture2D(&dtd, NULL, &m_pTempRT[0]);

	CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_pTempRT[0], &DownScaleDsrvd, &m_pTempSRV[0]);

	CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_pTempRT[0], &DescDownScaleUAV, &m_pTempUAV[0]);


	CDevice::GetInst()->GetDevice()->CreateTexture2D(&dtd, NULL, &m_pTempRT[1]);

	CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_pTempRT[1], &DownScaleDsrvd, &m_pTempSRV[1]);

	CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_pTempRT[1], &DescDownScaleUAV, &m_pTempUAV[1]);
	
	CDevice::GetInst()->GetDevice()->CreateTexture2D(&dtd, NULL, &m_pTempRT[2]);

	CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_pTempRT[2], &DownScaleDsrvd, &m_pTempSRV[2]);

	CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_pTempRT[2], &DescDownScaleUAV, &m_pTempUAV[2]);


	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Allocate bloom target
	CDevice::GetInst()->GetDevice()->CreateTexture2D(&dtd, NULL, &m_pBloomRT);

	CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_pBloomRT, &DownScaleDsrvd, &m_pBloomSRV);

	CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_pBloomRT, &DescDownScaleUAV, &m_pBloomUAV);

	

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Allocate Blurred target
	CDevice::GetInst()->GetDevice()->CreateTexture2D(&dtd, NULL, &m_pVerticalBlurRT);

	CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_pVerticalBlurRT, &DownScaleDsrvd, &m_pVerticalBlurSRV);

	CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_pVerticalBlurRT, &DescDownScaleUAV, &m_pVerticalBlurUAV);



	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Allocate down scaled luminance buffer
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	bufferDesc.StructureByteStride = sizeof(float);
	bufferDesc.ByteWidth = m_nDownScaleGroups * bufferDesc.StructureByteStride;
	bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&bufferDesc, NULL, &m_pDownScale1DBuffer);
	//V_RETURN(g_pDevice->CreateBuffer(&bufferDesc, NULL, &m_pDownScale1DBuffer));
	//DXUT_SetDebugName(m_pDownScale1DBuffer, "PostFX - Down Scale 1D Buffer");

	D3D11_UNORDERED_ACCESS_VIEW_DESC DescUAV;
	ZeroMemory(&DescUAV, sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
	DescUAV.Format = DXGI_FORMAT_UNKNOWN;
	DescUAV.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	DescUAV.Buffer.NumElements = m_nDownScaleGroups;

	CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_pDownScale1DBuffer, &DescUAV, &m_pDownScale1DUAV);
	/*V_RETURN(g_pDevice->CreateUnorderedAccessView(m_pDownScale1DBuffer, &DescUAV, &m_pDownScale1DUAV));
	DXUT_SetDebugName(m_pDownScale1DSRV, "PostFX - Luminance Down Scale 1D SRV");*/

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Allocate average luminance buffer
	D3D11_SHADER_RESOURCE_VIEW_DESC dsrvd;
	ZeroMemory(&dsrvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	dsrvd.Format = DXGI_FORMAT_UNKNOWN;
	dsrvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	dsrvd.Buffer.NumElements = m_nDownScaleGroups;

	CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_pDownScale1DBuffer, &dsrvd, &m_pDownScale1DSRV);
	/*V_RETURN(g_pDevice->CreateShaderResourceView(m_pDownScale1DBuffer, &dsrvd, &m_pDownScale1DSRV));
	DXUT_SetDebugName(m_pDownScale1DSRV, "PostFX - Down Scale 1D SRV");*/

	bufferDesc.ByteWidth = sizeof(float);
	CDevice::GetInst()->GetDevice()->CreateBuffer(&bufferDesc, NULL, &m_pAvgLumBuffer);
	/*V_RETURN(g_pDevice->CreateBuffer(&bufferDesc, NULL, &m_pAvgLumBuffer));
	DXUT_SetDebugName(m_pAvgLumBuffer, "PostFX - Average Luminance Buffer");*/
	CDevice::GetInst()->GetDevice()->CreateBuffer(&bufferDesc, NULL, &m_pPrevAvgLumBuffer);

	DescUAV.Buffer.NumElements = 1;
	CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_pAvgLumBuffer, &DescUAV, &m_pAvgLumUAV);
	/*V_RETURN(g_pDevice->CreateUnorderedAccessView(m_pAvgLumBuffer, &DescUAV, &m_pAvgLumUAV));
	DXUT_SetDebugName(m_pAvgLumUAV, "PostFX - Average Luminance UAV");*/
	CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_pPrevAvgLumBuffer, &DescUAV, &m_pPrevAvgLumUAV);

	dsrvd.Buffer.NumElements = 1;
	CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_pAvgLumBuffer, &dsrvd, &m_pAvgLumSRV);
	/*V_RETURN(g_pDevice->CreateShaderResourceView(m_pAvgLumBuffer, &dsrvd, &m_pAvgLumSRV));
	DXUT_SetDebugName(m_pAvgLumSRV, "PostFX - Average Luminance SRV");*/
	CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_pPrevAvgLumBuffer, &dsrvd, &m_pPrevAvgLumSRV);

	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.ByteWidth = sizeof(TDownScaleCB);

	CDevice::GetInst()->GetDevice()->CreateBuffer(&bufferDesc, NULL, &m_pDownScaleCB);
	/*V_RETURN(g_pDevice->CreateBuffer(&bufferDesc, NULL, &m_pDownScaleCB));
	DXUT_SetDebugName(m_pDownScaleCB, "PostFX - Down Scale CB");*/

	bufferDesc.ByteWidth = sizeof(TFinalPassCB);
	CDevice::GetInst()->GetDevice()->CreateBuffer(&bufferDesc, NULL, &m_pFinalPassCB);
	/*V_RETURN(g_pDevice->CreateBuffer(&bufferDesc, NULL, &m_pFinalPassCB));
	DXUT_SetDebugName(m_pFinalPassCB, "PostFX - Final Pass CB");*/

	// Compile the shaders
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pShaderBlob = NULL;
	TCHAR   FullPath[MAX_PATH] = {};
	const PathInfo* Info = CPathManager::GetInst()->FindPath("Shader");
	if (Info)
		lstrcpy(FullPath, Info->Path);
	lstrcat(FullPath, TEXT("PostDownScaleFX.fx"));
	ID3DBlob* Error = nullptr;

	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"DownScaleFirstPass", "cs_5_0", dwShaderFlags, 0, &pShaderBlob, &Error)))
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		OutputDebugStringA("\n");

		return false;
	}
	CDevice::GetInst()->GetDevice()->CreateComputeShader(pShaderBlob->GetBufferPointer(),
		pShaderBlob->GetBufferSize(), NULL, &m_pDownScaleFirstPassCS);

	SAFE_RELEASE(pShaderBlob);
	SAFE_RELEASE(Error);

	////////////
	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"DownScaleSecondPass", "cs_5_0", dwShaderFlags, 0, &pShaderBlob, &Error)))
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		OutputDebugStringA("\n");

		return false;
	}
	CDevice::GetInst()->GetDevice()->CreateComputeShader(pShaderBlob->GetBufferPointer(),
		pShaderBlob->GetBufferSize(), NULL, &m_pDownScaleSecondPassCS);

	SAFE_RELEASE(pShaderBlob);
	SAFE_RELEASE(Error);

	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"BloomReveal", "cs_5_0", dwShaderFlags, 0, &pShaderBlob, &Error)))
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		OutputDebugStringA("\n");

		return false;
	}
	CDevice::GetInst()->GetDevice()->CreateComputeShader(pShaderBlob->GetBufferPointer(),
		pShaderBlob->GetBufferSize(), NULL, &m_pBloomRevealCS);

	SAFE_RELEASE(pShaderBlob);
	SAFE_RELEASE(Error);

	///////////////// 




	TCHAR   FullPath1[MAX_PATH] = {};
	const PathInfo* Info1 = CPathManager::GetInst()->FindPath("Shader");
	if (Info1)
		lstrcpy(FullPath1, Info1->Path);
	lstrcat(FullPath1, TEXT("PostFX.fx"));

	if (FAILED(D3DCompileFromFile(FullPath1, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"FullScreenQuadVS", "vs_5_0", dwShaderFlags, 0, &pShaderBlob, &Error)))
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		OutputDebugStringA("\n");

		return false;
	}
	CDevice::GetInst()->GetDevice()->CreateVertexShader(pShaderBlob->GetBufferPointer(),
		pShaderBlob->GetBufferSize(), NULL, &m_pFullScreenQuadVS);

	SAFE_RELEASE(pShaderBlob);
	SAFE_RELEASE(Error);

	//////////////////



	if (FAILED(D3DCompileFromFile(FullPath1, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"FinalPassPS", "ps_5_0", dwShaderFlags, 0, &pShaderBlob, &Error)))
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		OutputDebugStringA("\n");

		return false;
	}
	CDevice::GetInst()->GetDevice()->CreatePixelShader(pShaderBlob->GetBufferPointer(),
		pShaderBlob->GetBufferSize(), NULL, &m_pFinalPassPS);

	SAFE_RELEASE(pShaderBlob);
	SAFE_RELEASE(Error);




	TCHAR   FullPath2[MAX_PATH] = {};

	if (Info1)
		lstrcpy(FullPath2, Info1->Path);

	lstrcat(FullPath2, TEXT("Blur.fx"));



	if (FAILED(D3DCompileFromFile(FullPath2, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VerticalFilter", "cs_5_0", dwShaderFlags, 0, &pShaderBlob, &Error)))
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		OutputDebugStringA("\n");

		return false;
	}
	CDevice::GetInst()->GetDevice()->CreateComputeShader(pShaderBlob->GetBufferPointer(),
		pShaderBlob->GetBufferSize(), NULL, &m_pVerticalBlurCS);

	SAFE_RELEASE(pShaderBlob);
	SAFE_RELEASE(Error);



	if (FAILED(D3DCompileFromFile(FullPath2, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"HorizFilter", "cs_5_0", dwShaderFlags, 0, &pShaderBlob, &Error)))
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		OutputDebugStringA("\n");

		return false;
	}
	CDevice::GetInst()->GetDevice()->CreateComputeShader(pShaderBlob->GetBufferPointer(),
		pShaderBlob->GetBufferSize(), NULL, &m_pHorizontalBlurCS);

	SAFE_RELEASE(pShaderBlob);
	SAFE_RELEASE(Error);


	return true;
}

void CHDR::Deinit()
{
	SAFE_RELEASE(m_pDownScaleRT);
	SAFE_RELEASE(m_pDownScaleSRV);
	SAFE_RELEASE(m_pDownScaleUAV);
	SAFE_RELEASE(m_pTempRT[0]);
	SAFE_RELEASE(m_pTempSRV[0]);
	SAFE_RELEASE(m_pTempUAV[0]);
	SAFE_RELEASE(m_pTempRT[1]);
	SAFE_RELEASE(m_pTempSRV[1]);
	SAFE_RELEASE(m_pTempUAV[1]);
	SAFE_RELEASE(m_pBloomRT);
	SAFE_RELEASE(m_pBloomSRV);
	SAFE_RELEASE(m_pBloomUAV);
	SAFE_RELEASE(m_pBloomRevealCS);
	SAFE_RELEASE(m_pDownScale1DBuffer);
	SAFE_RELEASE(m_pDownScale1DUAV);
	SAFE_RELEASE(m_pDownScale1DSRV);
	SAFE_RELEASE(m_pDownScaleCB);
	SAFE_RELEASE(m_pFinalPassCB);
	SAFE_RELEASE(m_pAvgLumBuffer);
	SAFE_RELEASE(m_pAvgLumUAV);
	SAFE_RELEASE(m_pAvgLumSRV);
	SAFE_RELEASE(m_pDownScaleFirstPassCS);
	SAFE_RELEASE(m_pDownScaleSecondPassCS);
	SAFE_RELEASE(m_pFullScreenQuadVS);
	SAFE_RELEASE(m_pFinalPassPS);
	SAFE_RELEASE(SampPoint);
	SAFE_RELEASE(m_pPrevAvgLumBuffer);
	SAFE_RELEASE(m_pPrevAvgLumUAV);
	SAFE_RELEASE(m_pPrevAvgLumSRV);

}

void CHDR::PostProcessing(ID3D11DeviceContext* pd3dImmediateContext, ID3D11ShaderResourceView* pHDRSRV, ID3D11RenderTargetView* pLDRRTV)
{
	// Down scale the HDR image
	ID3D11RenderTargetView* rt[1] = { NULL };

	DownScale(pd3dImmediateContext, pHDRSRV);

	Bloom(pd3dImmediateContext);

	Blur(pd3dImmediateContext, m_pTempSRV[0], m_pBloomUAV);

	// Do the final pass
	rt[0] = pLDRRTV;
	FinalPass(pd3dImmediateContext, pHDRSRV);

	// Swap the previous frame average luminance
	ID3D11Buffer* pTempBuffer = m_pAvgLumBuffer;
	ID3D11UnorderedAccessView* pTempUAV = m_pAvgLumUAV;
	ID3D11ShaderResourceView* p_TempSRV = m_pAvgLumSRV;
	m_pAvgLumBuffer = m_pPrevAvgLumBuffer;
	m_pAvgLumUAV = m_pPrevAvgLumUAV;
	m_pAvgLumSRV = m_pPrevAvgLumSRV;
	m_pPrevAvgLumBuffer = pTempBuffer;
	m_pPrevAvgLumUAV = pTempUAV;
	m_pPrevAvgLumSRV = p_TempSRV;
}

void CHDR::DownScale(ID3D11DeviceContext* pd3dImmediateContext, ID3D11ShaderResourceView* pHDRSRV)
{
	// Output
	ID3D11UnorderedAccessView* arrUAVs[2] = { m_pDownScale1DUAV, m_pDownScaleUAV };
	pd3dImmediateContext->CSSetUnorderedAccessViews(0, 2, arrUAVs, NULL);

	// Input
	ID3D11ShaderResourceView* arrViews[2] = { pHDRSRV, NULL };
	pd3dImmediateContext->CSSetShaderResources(0, 1, arrViews);

	// Constants
	D3D11_MAPPED_SUBRESOURCE MappedResource;
	pd3dImmediateContext->Map(m_pDownScaleCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
	TDownScaleCB* pDownScale = (TDownScaleCB*)MappedResource.pData;
	pDownScale->nWidth = m_nWidth / 4;
	pDownScale->nHeight = m_nHeight / 4;
	pDownScale->nTotalPixels = pDownScale->nWidth * pDownScale->nHeight;
	pDownScale->nGroupSize = m_nDownScaleGroups;
	pDownScale->fBloomThreshold = m_fBloomThreshold;
	pDownScale->fAdaptation = m_fAdaptation;
	pd3dImmediateContext->Unmap(m_pDownScaleCB, 0);
	ID3D11Buffer* arrConstBuffers[1] = { m_pDownScaleCB };

	pd3dImmediateContext->CSSetConstantBuffers(0, 1, arrConstBuffers);

	// Shader
	pd3dImmediateContext->CSSetShader(m_pDownScaleFirstPassCS, NULL, 0);


	// Execute the downscales first pass with enough groups to cover the entire full res HDR buffer
	pd3dImmediateContext->Dispatch(m_nDownScaleGroups, 1, 1);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Second pass - reduce to a single pixel

	// Outoput
	ZeroMemory(arrUAVs, sizeof(arrUAVs));
	arrUAVs[0] = m_pAvgLumUAV;
	pd3dImmediateContext->CSSetUnorderedAccessViews(0, 2, arrUAVs, NULL);

	// Input
	arrViews[0] = m_pDownScale1DSRV;
	arrViews[1] = m_pPrevAvgLumSRV;
	pd3dImmediateContext->CSSetShaderResources(0, 2, arrViews);

	// Shader
	pd3dImmediateContext->CSSetShader(m_pDownScaleSecondPassCS, NULL, 0);

	// Excute with a single group - this group has enough threads to process all the pixels
	pd3dImmediateContext->Dispatch(1, 1, 1);

	// Cleanup
	pd3dImmediateContext->CSSetShader(NULL, NULL, 0);
	ZeroMemory(arrViews, sizeof(arrViews));
	pd3dImmediateContext->CSSetShaderResources(0, 2, arrViews);
	ZeroMemory(arrUAVs, sizeof(arrUAVs));
	pd3dImmediateContext->CSSetUnorderedAccessViews(0, 2, arrUAVs, (UINT*)(&arrUAVs));
}

void CHDR::FinalPass(ID3D11DeviceContext* pd3dImmediateContext, ID3D11ShaderResourceView* pHDRSRV)
{
	ID3D11ShaderResourceView* arrViews[4] = { pHDRSRV, m_pAvgLumSRV, m_pBloomSRV, m_pDownScaleSRV };
	pd3dImmediateContext->PSSetShaderResources(0, 4, arrViews);

	// Constants
	float fQ = 1000.f / 1000.f - 0.1f;

	D3D11_MAPPED_SUBRESOURCE MappedResource;
	pd3dImmediateContext->Map(m_pFinalPassCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
	TFinalPassCB* pFinalPass = (TFinalPassCB*)MappedResource.pData;
	pFinalPass->fMiddleGrey = m_fMiddleGrey;
	pFinalPass->fLumWhiteSqr = m_fWhite;
	pFinalPass->fLumWhiteSqr *= pFinalPass->fMiddleGrey; // Scale by the middle grey value
	pFinalPass->fLumWhiteSqr *= pFinalPass->fLumWhiteSqr; // Squre
	pFinalPass->fBloomScale = m_fBloomScale; // Squre
	pFinalPass->iEnableBlur = m_iEnableBlur; // Squre
	pFinalPass->fProjectionValue.x = -0.1f * fQ; // -0.1f
	pFinalPass->fProjectionValue.y = -fQ;		 // -0.9f
	pFinalPass->fDOFValue = Vector2(m_fNearStart, m_fFarStart);


	pd3dImmediateContext->Unmap(m_pFinalPassCB, 0);

	ID3D11Buffer* arrConstBuffers[1] = { m_pFinalPassCB };
	pd3dImmediateContext->PSSetConstantBuffers(0, 1, arrConstBuffers);


	ID3D11SamplerState* arrSamplers[2] = { SampPoint, SampLinear };
	pd3dImmediateContext->PSSetSamplers(0, 2, arrSamplers);

	// Set the shaders
	pd3dImmediateContext->VSSetShader(m_pFullScreenQuadVS, NULL, 0);
	pd3dImmediateContext->PSSetShader(m_pFinalPassPS, NULL, 0);
}

void CHDR::Bloom(ID3D11DeviceContext* pd3dImmediateContext)
{
	ID3D11ShaderResourceView* arrViews[2] = { m_pDownScaleSRV, m_pAvgLumSRV };
	pd3dImmediateContext->CSSetShaderResources(0, 2, arrViews);

	// Output
	ID3D11UnorderedAccessView* arrUAVs[2] = { m_pTempUAV[0] , m_pTempUAV[2] };
	pd3dImmediateContext->CSSetUnorderedAccessViews(0, 2, arrUAVs, NULL);

	// Shader
	pd3dImmediateContext->CSSetShader(m_pBloomRevealCS, NULL, 0);

	// Execute the downscales first pass with enough groups to cover the entire full res HDR buffer
	pd3dImmediateContext->Dispatch(m_nDownScaleGroups, 1, 1);

	// Cleanup

	pd3dImmediateContext->CSSetShader(NULL, NULL, 0);
	ZeroMemory(arrViews, sizeof(arrViews));
	pd3dImmediateContext->CSSetShaderResources(0, 2, arrViews);
	ZeroMemory(arrUAVs, sizeof(arrUAVs));
	pd3dImmediateContext->CSSetUnorderedAccessViews(0, 2, arrUAVs, NULL);
}

void CHDR::Blur(ID3D11DeviceContext* pd3dImmediateContext, ID3D11ShaderResourceView* pInput, ID3D11UnorderedAccessView* pOutput)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Second pass - horizontal gaussian filter

	// Output
	ID3D11UnorderedAccessView* arrUAVs[1] = { m_pTempUAV[1] };
	pd3dImmediateContext->CSSetUnorderedAccessViews(0, 1, arrUAVs, NULL);

	// Input
	ID3D11ShaderResourceView* arrViews[1] = { pInput };		// pInput << Bloom Ã³¸®µÈ SRV
	pd3dImmediateContext->CSSetShaderResources(0, 1, arrViews);

	// Shader
	pd3dImmediateContext->CSSetShader(m_pHorizontalBlurCS, NULL, 0);

	// Execute the horizontal filter
	pd3dImmediateContext->Dispatch((UINT)ceil((m_nWidth / 4.0f) / (128.0f - 12.0f)), (UINT)ceil(m_nHeight / 4.0f), 1);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// First pass - vertical gaussian filter

	// Output
	arrUAVs[0] = pOutput;
	pd3dImmediateContext->CSSetUnorderedAccessViews(0, 1, arrUAVs, NULL);
	
	// Input
	arrViews[0] = m_pTempSRV[1];
	pd3dImmediateContext->CSSetShaderResources(0, 1, arrViews);
	
	// Shader
	pd3dImmediateContext->CSSetShader(m_pVerticalBlurCS, NULL, 0);
	
	// Execute the vertical filter
	pd3dImmediateContext->Dispatch((UINT)ceil(m_nWidth / 4.0f), (UINT)ceil((m_nHeight / 4.0f) / (128.0f - 12.0f)), 1);




	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// First pass - vertical gaussian filter FOR Only just vertical filtering

	// Output
	arrUAVs[0] = m_pVerticalBlurUAV;
	pd3dImmediateContext->CSSetUnorderedAccessViews(0, 1, arrUAVs, NULL);
	
	// Input
	arrViews[0] = m_pTempSRV[2];
	pd3dImmediateContext->CSSetShaderResources(0, 1, arrViews);
	
	pd3dImmediateContext->CSSetShader(m_pVerticalBlurCS, NULL, 0);
	pd3dImmediateContext->Dispatch((UINT)ceil(m_nWidth / 4.0f), (UINT)ceil((m_nHeight / 4.0f) / (128.0f - 12.0f)), 1);
	

	ID3D11Buffer* arrConstBuffers[1] = { m_pDownScaleCB };

	ZeroMemory(&arrConstBuffers, sizeof(arrConstBuffers));
	pd3dImmediateContext->CSSetConstantBuffers(0, 1, arrConstBuffers);

	pd3dImmediateContext->CSSetShader(NULL, NULL, 0);
	ZeroMemory(arrViews, sizeof(arrViews));
	pd3dImmediateContext->CSSetShaderResources(0, 1, arrViews);
	ZeroMemory(arrUAVs, sizeof(arrUAVs));
	pd3dImmediateContext->CSSetUnorderedAccessViews(0, 1, arrUAVs, NULL);
}


void CHDR::CleanUp(ID3D11DeviceContext* pd3dImmediateContext)
{
	ID3D11ShaderResourceView* arrViews[4];
	ID3D11Buffer* arrConstBuffers[1];
	ZeroMemory(arrViews, sizeof(arrViews));
	pd3dImmediateContext->PSSetShaderResources(0, 4, arrViews);
	ZeroMemory(arrConstBuffers, sizeof(arrConstBuffers));
	pd3dImmediateContext->PSSetConstantBuffers(0, 1, arrConstBuffers);
	pd3dImmediateContext->VSSetShader(NULL, NULL, 0);
	pd3dImmediateContext->PSSetShader(NULL, NULL, 0);
}