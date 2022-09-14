#include "PickingComputeShader.h"

CPickingComputeShader::CPickingComputeShader()
{
	SetTypeID<CPickingComputeShader>();
}

CPickingComputeShader::CPickingComputeShader(const CPickingComputeShader& shader) :
	CComputeShader(shader)
{
}

CPickingComputeShader::~CPickingComputeShader()
{
}

bool CPickingComputeShader::Init()
{
	if (!LoadComputeShader("PickingCS", TEXT("Picking.fx"), SHADER_PATH))
		return false;

	return true;
}

CPickingComputeShader* CPickingComputeShader::Clone()
{
	return DBG_NEW CPickingComputeShader(*this);
}
