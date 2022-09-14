#pragma once

#include "IMGUIWindow.h"

class CInfoWindow :
	public CIMGUIWindow
{
	friend class CEditorManager;

public:
	CInfoWindow();
	virtual ~CInfoWindow();

private:
	class CHierarchyWindow* m_Hierarchy;
	class CIMGUIText*	m_CamUI;
	class CIMGUIText*	m_DDTUI;
	class CIMGUIText*	m_ObjNameUI;
	class CIMGUIText*	m_ObjPosUI;
	std::string			m_ObjName;
	Vector3				m_DDTPos;
	Vector3				m_CamPos;
	Vector3				m_ObjPos;
	char				m_DDTPosText[64];
	char				m_CamPosText[64];
	char				m_ObjPosText[64];
	bool				m_UseDDTPosText;

public:
	void SetObjName(const std::string& Name)
	{
		m_ObjName = Name;
	}

	void SetObjPos(const Vector3& Pos)
	{
		m_ObjPos = Pos;
	}

	void SetDDTPos(const Vector3& DDTPos)
	{
		m_DDTPos = DDTPos;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void ViewCamPos();
	void ViewDDTPos();
	void ViewSelectObject();
};

