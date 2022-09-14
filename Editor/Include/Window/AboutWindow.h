#pragma once

#include "IMGUIWindow.h"

class CAboutWindow :
	public CIMGUIWindow
{
	friend class CEditorManager;

public:
	CAboutWindow();
	virtual ~CAboutWindow();

public:
	virtual bool Init();
};

