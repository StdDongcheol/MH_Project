#pragma once
#include "GraphicShader.h"
class CRimLightShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CRimLightShader();
    virtual ~CRimLightShader();

public:
    virtual bool Init();
};

