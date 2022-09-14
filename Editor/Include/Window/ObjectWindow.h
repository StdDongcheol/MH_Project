#pragma once

#include "IMGUIWindow.h"

class CObjectWindow :
	public CIMGUIWindow
{
	friend class CEditorManager;

public:
	CObjectWindow();
	virtual ~CObjectWindow();
	
private:
	CharacterInfo	m_CharacterInfo;
	bool			m_BrushMode;
	int				m_BrushType;
	int				m_BrushEditType;
	class CIMGUITree* m_CharacterTree;
	class CIMGUITree* m_LandScapeTree;
	class CIMGUICheckBox* m_BrushModeCheckBox;
	class CIMGUIComboBox* m_TypeComboBox;
	class CIMGUIComboBox* m_MonsterComboBox;
	class CIMGUIComboBox* m_FieldObjComboBox;
	class CIMGUIComboBox* m_TextureTypeComboBox;
	class CIMGUIText* m_BrushScaleText;
	class CIMGUITextInput* m_AttMin;
	class CIMGUITextInput* m_AttMax;
	class CIMGUITextInput* m_HP;
	class CIMGUITextInput* m_Stamina;
	class CIMGUITextInput* m_Speed;
	class CIMGUITextInput* m_LandScapeSize;
	class CIMGUITextInput* m_LandScapeTextureNum;
	class CIMGUITextInput* m_FieldObjNum;
	class CIMGUITextInput* m_BrushScale;
	class CIMGUIButton* m_ModifyButton;
	class CIMGUIButton* m_SaveButton;
	class CIMGUIButton* m_LoadButton;
	class CIMGUIButton* m_NavButton;
	class CIMGUIRadio* m_CircleBrushTypeRadio;
	class CIMGUIRadio* m_RectBrushTypeRadio;
	class CIMGUIRadio* m_HeightRadio;
	class CIMGUIRadio* m_SplattingRadio;
	class CIMGUIGizmo* m_Gizmo;
	class CIMGUISameLine* m_LandScapeCountLine;
	class CIMGUISameLine* m_MonsterTypeLine;
	class CIMGUISameLine* m_FieldTypeLine;
	class CIMGUISameLine* m_BrushScaleLine;

public:
	int GetBrushEditType()	const
	{
		if (!m_BrushMode)
			return -1;

		return m_BrushEditType;
	}

	int GetBrushType()	const
	{
		if (!m_BrushMode)
			return (int)Brush_Type::Circle;

		return m_BrushType;
	}

	bool IsBrushMode()	const
	{
		return m_BrushMode;
	}
	
	int GetLandScapeType()	const;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void SetTarget(class CGameObject* obj);
	void ClearTarget();

private:
	void SetBrushScale();

public:
	void Refresh(Object_Type Type, const CharacterInfo& Info, CSharedPtr<class CGameObject> SelectObject);

private:
	void CreateAuto();
	void DeleteButton();
	void ModifyButton();
	void NavButton();

public:
	void Reset();

private:
	void HideComboBoxUpdater();
	void HideCheckBoxUpdater(const bool& IsCheck, class CIMGUIWidget* HideWidget); // 위젯을 보이고 숨기는 체크박스
	void HideRadioUpdater();
	void HideGizmoUpdater();

private:
	void WheelUp(float DeltaTime);
	void WheelDown(float DeltaTime);

private:
	void LandScapeUpdater();

private:
	void IntInputUpdater();

private:
	int GetSelectTextureIndex();

private:
	void RefreshCharacterInfo(const CharacterInfo& Info, Object_Type Type);

private:
	void RefreshFieldObjIndex(int Index, const char* Item);
};