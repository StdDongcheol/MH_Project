#pragma once
#include "GraphicShader.h"
class CEffectShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CEffectShader();
    virtual ~CEffectShader();

public:
    virtual bool Init();
};

