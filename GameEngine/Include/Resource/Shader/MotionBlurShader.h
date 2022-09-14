#pragma once
#include "GraphicShader.h"

class CMotionBlurShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CMotionBlurShader();
    virtual ~CMotionBlurShader();

public:
    virtual bool Init();
};

