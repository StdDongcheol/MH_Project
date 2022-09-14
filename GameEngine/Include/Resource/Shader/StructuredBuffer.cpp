
#include "StructuredBuffer.h"
#include "../../Device.h"

CStructuredBuffer::CStructuredBuffer()	:
	m_Buffer(nullptr),
	m_SRV(nullptr),
	m_UAV(nullptr),
	m_InputBuffer(nullptr),
	m_OutputBuffer(nullptr),
	m_InputData(nullptr),
	m_Desc{},
	m_InputSize(0),
	m_InputCount(0),
	m_OutputSize(0),
	m_OutputCount(0)
{
}

CStructuredBuffer::CStructuredBuffer(const CStructuredBuffer& buffer)
{
	*this = buffer;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&m_Desc, nullptr, &m_Buffer);

	D3D11_SHADER_RESOURCE_VIEW_DESC	SRVDesc = {};

	SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	SRVDesc.BufferEx.FirstElement = 0;
	SRVDesc.BufferEx.Flags = 0;
	SRVDesc.BufferEx.NumElements = m_Count;

	CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_Buffer, &SRVDesc, &m_SRV);

	if (!m_Dynamic)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC	UAVDesc = {};

		UAVDesc.Format = DXGI_FORMAT_UNKNOWN;
		UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		UAVDesc.Buffer.FirstElement = 0;
		UAVDesc.Buffer.Flags = 0;
		UAVDesc.Buffer.NumElements = m_Count;

		CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_Buffer, &UAVDesc, &m_UAV);
	}
}

CStructuredBuffer::~CStructuredBuffer()
{
	SAFE_RELEASE(m_SRV);
	SAFE_RELEASE(m_UAV);
	//SAFE_RELEASE(m_ResultBuffer);
	//SAFE_RELEASE(m_OutputBuffer);
	//SAFE_RELEASE(m_InputBuffer);
	SAFE_RELEASE(m_Buffer);
}

bool CStructuredBuffer::Init(const std::string& Name, unsigned int Size, unsigned int Count, int Register,
	bool Dynamic, int StructuredBufferShaderType)
{
	SAFE_RELEASE(m_SRV);
	SAFE_RELEASE(m_UAV);
	SAFE_RELEASE(m_Buffer);

	m_Dynamic = Dynamic;
	m_Name = Name;
	m_Size = Size;
	m_Count = Count;
	m_Register = Register;
	m_StructuredBufferShaderType = StructuredBufferShaderType;

	m_Desc.ByteWidth = m_Size * m_Count;
	m_Desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	m_Desc.StructureByteStride = m_Size;

	if (m_Dynamic)
	{
		m_Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		m_Desc.Usage = D3D11_USAGE_DYNAMIC;
		m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	else
	{
		m_Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		m_Desc.Usage = D3D11_USAGE_DEFAULT;
	}

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&m_Desc, nullptr, &m_Buffer)))
		return false;

	D3D11_SHADER_RESOURCE_VIEW_DESC	SRVDesc = {};

	SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	SRVDesc.BufferEx.FirstElement = 0;
	SRVDesc.BufferEx.Flags = 0;
	SRVDesc.BufferEx.NumElements = m_Count;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_Buffer, &SRVDesc, &m_SRV)))
		return false;

	if (!m_Dynamic)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC	UAVDesc = {};

		UAVDesc.Format = DXGI_FORMAT_UNKNOWN;
		UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		UAVDesc.Buffer.FirstElement = 0;
		UAVDesc.Buffer.Flags = 0;
		UAVDesc.Buffer.NumElements = m_Count;

		if (FAILED(CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_Buffer, &UAVDesc, &m_UAV)))
			return false;
	}

	return true;
}

bool CStructuredBuffer::Init(const std::string& Name, unsigned int Size, unsigned int Count, int Register, D3D11_USAGE Usage, UINT BindFlag, UINT CpuFlag, bool Dynamic, int StructuredBufferShaderType)
{
	SAFE_RELEASE(m_SRV);
	SAFE_RELEASE(m_UAV);
	SAFE_RELEASE(m_Buffer);

	m_Dynamic = Dynamic;
	m_Name = Name;
	m_Size = Size;
	m_Count = Count;
	m_Register = Register;
	m_StructuredBufferShaderType = StructuredBufferShaderType;

	m_Desc.ByteWidth = m_Size * m_Count;
	m_Desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	m_Desc.StructureByteStride = m_Size;

	m_Desc.BindFlags = BindFlag;
	m_Desc.Usage = Usage;
	m_Desc.CPUAccessFlags = CpuFlag;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&m_Desc, nullptr, &m_Buffer)))
		return false;

	D3D11_SHADER_RESOURCE_VIEW_DESC	SRVDesc = {};

	SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	SRVDesc.BufferEx.FirstElement = 0;
	SRVDesc.BufferEx.Flags = 0;
	SRVDesc.BufferEx.NumElements = m_Count;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateShaderResourceView(m_Buffer, &SRVDesc, &m_SRV)))
		return false;

	D3D11_UNORDERED_ACCESS_VIEW_DESC	UAVDesc = {};

	UAVDesc.Format = DXGI_FORMAT_UNKNOWN;
	UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	UAVDesc.Buffer.FirstElement = 0;
	UAVDesc.Buffer.Flags = 0;
	UAVDesc.Buffer.NumElements = m_Count;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(m_Buffer, &UAVDesc, &m_UAV)))
		return false;

	return true;
}

void CStructuredBuffer::UpdateBuffer(void* Data, int Count)
{
	if (!m_Dynamic)
		return;

	D3D11_MAPPED_SUBRESOURCE	Map = {};

	CDevice::GetInst()->GetContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Map);

	memcpy(Map.pData, Data, m_Size * Count);

	CDevice::GetInst()->GetContext()->Unmap(m_Buffer, 0);
}

CStructuredBuffer* CStructuredBuffer::Clone()
{
	return new CStructuredBuffer(*this);
}

void CStructuredBuffer::SetShader()
{
	if (m_Dynamic)
	{
		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Vertex)
			CDevice::GetInst()->GetContext()->VSSetShaderResources(m_Register, 1, &m_SRV);

		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Pixel)
			CDevice::GetInst()->GetContext()->PSSetShaderResources(m_Register, 1, &m_SRV);

		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Domain)
			CDevice::GetInst()->GetContext()->DSSetShaderResources(m_Register, 1, &m_SRV);

		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Hull)
			CDevice::GetInst()->GetContext()->HSSetShaderResources(m_Register, 1, &m_SRV);

		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Geometry)
			CDevice::GetInst()->GetContext()->GSSetShaderResources(m_Register, 1, &m_SRV);

		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Compute)
			CDevice::GetInst()->GetContext()->CSSetShaderResources(m_Register, 1, &m_SRV);
	}

	else
	{
		unsigned int	Count = -1;
		CDevice::GetInst()->GetContext()->CSSetUnorderedAccessViews(m_Register, 1, &m_UAV, &Count);
	}
}

void CStructuredBuffer::ResetShader()
{
	if (m_Dynamic)
	{
		ID3D11ShaderResourceView* SRV = nullptr;

		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Vertex)
			CDevice::GetInst()->GetContext()->VSSetShaderResources(m_Register, 1, &SRV);

		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Pixel)
			CDevice::GetInst()->GetContext()->PSSetShaderResources(m_Register, 1, &SRV);

		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Domain)
			CDevice::GetInst()->GetContext()->DSSetShaderResources(m_Register, 1, &SRV);

		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Hull)
			CDevice::GetInst()->GetContext()->HSSetShaderResources(m_Register, 1, &SRV);

		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Geometry)
			CDevice::GetInst()->GetContext()->GSSetShaderResources(m_Register, 1, &SRV);

		if (m_StructuredBufferShaderType & (int)Buffer_Shader_Type::Compute)
			CDevice::GetInst()->GetContext()->CSSetShaderResources(m_Register, 1, &SRV);
	}

	else
	{
		unsigned int	Count = -1;
		ID3D11UnorderedAccessView* UAV = nullptr;
		CDevice::GetInst()->GetContext()->CSSetUnorderedAccessViews(m_Register, 1, &UAV, &Count);
	}
}

void CStructuredBuffer::SetShader(int Register, int StructuredBufferShaderType)
{
	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Vertex)
		CDevice::GetInst()->GetContext()->VSSetShaderResources(Register, 1, &m_SRV);

	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Pixel)
		CDevice::GetInst()->GetContext()->PSSetShaderResources(Register, 1, &m_SRV);

	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Domain)
		CDevice::GetInst()->GetContext()->DSSetShaderResources(Register, 1, &m_SRV);

	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Hull)
		CDevice::GetInst()->GetContext()->HSSetShaderResources(Register, 1, &m_SRV);

	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Geometry)
		CDevice::GetInst()->GetContext()->GSSetShaderResources(Register, 1, &m_SRV);

	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Compute)
		CDevice::GetInst()->GetContext()->CSSetShaderResources(Register, 1, &m_SRV);
	
}

void CStructuredBuffer::ResetShader(int Register, int StructuredBufferShaderType)
{
	ID3D11ShaderResourceView* SRV = nullptr;

	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Vertex)
		CDevice::GetInst()->GetContext()->VSSetShaderResources(Register, 1, &SRV);

	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Pixel)
		CDevice::GetInst()->GetContext()->PSSetShaderResources(Register, 1, &SRV);

	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Domain)
		CDevice::GetInst()->GetContext()->DSSetShaderResources(Register, 1, &SRV);

	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Hull)
		CDevice::GetInst()->GetContext()->HSSetShaderResources(Register, 1, &SRV);

	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Geometry)
		CDevice::GetInst()->GetContext()->GSSetShaderResources(Register, 1, &SRV);

	if (StructuredBufferShaderType & (int)Buffer_Shader_Type::Compute)
		CDevice::GetInst()->GetContext()->CSSetShaderResources(Register, 1, &SRV);
}

void CStructuredBuffer::CopyData(void* Data)
{
	D3D11_MAPPED_SUBRESOURCE	Map = {};

	CDevice::GetInst()->GetContext()->Map(m_Buffer, 0, D3D11_MAP_READ, 0, &Map);

	if (!Map.pData)
		return;

	memcpy(Data, Map.pData, m_Size * m_Count);

	CDevice::GetInst()->GetContext()->Unmap(m_Buffer, 0);
}

void CStructuredBuffer::CopyResource(CStructuredBuffer* Buffer)
{
	CDevice::GetInst()->GetContext()->CopyResource(Buffer->m_Buffer, m_Buffer);
}

void CStructuredBuffer::InitPicking(void* InputData, unsigned int InputSize, unsigned int InputCount, unsigned int OutputSize, unsigned int OutputCount)
{
	m_InputData = InputData;
	m_InputSize = InputSize;
	m_InputCount = InputCount;
	m_OutputSize = OutputSize;
	m_OutputCount = OutputCount;

	CreateInput();
	CreateSRV();
	CreateOutput();
	CreateUAV();
	CreateResult();
}

void CStructuredBuffer::Copy(void* Data, unsigned int Size)
{
	CDevice::GetInst()->GetContext()->CopyResource(m_ResultBuffer, m_OutputBuffer);

	D3D11_MAPPED_SUBRESOURCE subResource;

	CDevice::GetInst()->GetContext()->Map(m_ResultBuffer, 0, D3D11_MAP_READ, 0, &subResource);

	memcpy(Data, subResource.pData, Size);

	CDevice::GetInst()->GetContext()->Unmap(m_ResultBuffer, 0);
}

void CStructuredBuffer::CreateInput()
{
	ID3D11Buffer* buffer;

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = m_InputSize * m_InputCount;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = m_InputSize;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = m_InputData;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&desc, &initData, &buffer)))
		return;

	m_InputBuffer = (ID3D11Resource*)buffer;
}

void CStructuredBuffer::CreateSRV()
{
	ID3D11Buffer* buffer = (ID3D11Buffer*)m_InputBuffer;

	D3D11_BUFFER_DESC desc;
	buffer->GetDesc(&desc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDesc.BufferEx.FirstElement = 0;
	srvDesc.BufferEx.NumElements = m_InputCount;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateShaderResourceView(buffer, &srvDesc, &m_SRV)))
		return;
}

void CStructuredBuffer::CreateOutput()
{
	ID3D11Buffer* buffer;

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = m_OutputSize * m_OutputCount;
	desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = m_OutputSize;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&desc, nullptr, &buffer)))
		return;

	m_OutputBuffer = (ID3D11Resource*)buffer;
}

void CStructuredBuffer::CreateUAV()
{
	ID3D11Buffer* buffer = (ID3D11Buffer*)m_OutputBuffer;

	D3D11_BUFFER_DESC desc;
	buffer->GetDesc(&desc);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.Format = DXGI_FORMAT_UNKNOWN;
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.FirstElement = 0;
	uavDesc.Buffer.NumElements = m_OutputCount;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateUnorderedAccessView(buffer, &uavDesc, &m_UAV)))
		return;
}

void CStructuredBuffer::CreateResult()
{
	ID3D11Buffer* buffer;

	D3D11_BUFFER_DESC desc = {};
	((ID3D11Buffer*)m_OutputBuffer)->GetDesc(&desc);
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.MiscFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&desc, nullptr, &buffer)))
		return;

	m_ResultBuffer = (ID3D11Resource*)buffer;
}
