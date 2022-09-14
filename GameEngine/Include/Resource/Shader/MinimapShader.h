#pragma once
#include "GraphicShader.h"

class CMinimapShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CMinimapShader();
    virtual ~CMinimapShader();

public:
    virtual bool Init();
};

