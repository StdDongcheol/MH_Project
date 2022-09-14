#pragma once

#include "ComputeShader.h"

class CPickingComputeShader :
	public CComputeShader
{
	friend class CShaderManager;

protected:
	CPickingComputeShader();
	CPickingComputeShader(const CPickingComputeShader& shader);
	virtual ~CPickingComputeShader();

public:
	virtual bool Init();
	virtual CPickingComputeShader* Clone();

public:

};