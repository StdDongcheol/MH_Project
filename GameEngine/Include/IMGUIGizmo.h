#pragma once

#include "IMGUIWidget.h"

class CIMGUIGizmo :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUIGizmo();
	virtual ~CIMGUIGizmo();

private:
	CSharedPtr<class CCameraComponent>	m_Camera;
	class CGameObject*					m_Target;
	ImGuizmo::OPERATION					m_TargetOper;
	Matrix								m_matCamView;
	Matrix								m_matCamProj;
	Matrix								m_matTarget;
	float								m_CamView[16];
	float								m_CamProj[16];
	float								m_Result[16];
	float								m_Pos[3];
	float								m_Scale[3];
	float								m_Rot[3];
	float								m_Bounds[6];
	bool								m_Check;
	char								m_PosText[32];
	char								m_ScaleText[32];
	char								m_RotText[32];

public:
	float* GetPos()	
	{
		return m_Pos;
	}

	float* GetScale()
	{
		return m_Scale;
	}

	float* GetRot()
	{
		return m_Rot;
	}

public:
	void SetTarget(class CGameObject* Target)
	{
		m_Target = Target;

		m_Check = false;
	}

	void ClearTarget()
	{
		m_Target = nullptr;

		m_Check = false;
	}

public:
	virtual bool Init();
	virtual bool Render();

public:
	bool IsUsing()	const;
	virtual bool IsHovered()	const;

private:
	void MatrixToFloat();
	void EditTransform(float* matrix);
};

