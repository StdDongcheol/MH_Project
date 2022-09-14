#pragma once

#include "GameInfo.h"

class CIMGUIWindow
{
public:
	CIMGUIWindow();
	virtual ~CIMGUIWindow();

protected:
	std::string	m_Name;
	std::string	m_PopupTitle;
	bool	m_Open;
	bool	m_ModalPopup;
	bool	m_Start;
	bool	m_Focus;
	int		m_WindowFlag;
	std::vector<class CIMGUIWidget*>	m_vecWidget;
	std::vector<class CIMGUIWidget*>	m_vecPopupWidget;
	std::function<void(float)>					m_WheelUpFunc;
	std::function<void(float)>					m_WheelDownFunc;

public:
	bool IsFocus()	const
	{
		return m_Focus;
	}

	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}

	void AddWindowFlag(ImGuiWindowFlags_ Flag)
	{
		m_WindowFlag |= Flag;
	}

	void DeleteWindowFlag(ImGuiWindowFlags_ Flag)
	{
		m_WindowFlag &= ~Flag;
	}

	void EnableModalPopup()
	{
		m_ModalPopup = true;
	}

	void SetPopupWindowTitle(const std::string& Title)
	{
		m_PopupTitle = Title;
	}

public:
	void Open();
	void Close();
	void ClosePopup();
	class CIMGUIWidget* FindWidget(const std::string& Name);

public:
	bool IsKeyDown(unsigned char Key);
	bool IsKeyPush(unsigned char Key);
	bool IsKeyUp(unsigned char Key);

public:
	virtual bool Init();
	virtual bool Start();
	virtual void Update(float DeltaTime);

protected:
	template <typename T>
	void SetWheelUpCallback(T* Obj, void(T::* Func)(float))
	{
		m_WheelUpFunc = std::bind(Func, Obj, std::placeholders::_1);
	}

	template <typename T>
	void SetWheelDownCallback(T* Obj, void(T::* Func)(float))
	{
		m_WheelDownFunc = std::bind(Func, Obj, std::placeholders::_1);
	}

public:
	template <typename T>
	T* AddWidget(const std::string& Name, float Width = 100.f, float Height = 100.f)
	{
		T* Widget = DBG_NEW T;

		Widget->SetName(Name);
		Widget->SetOwner(this);
		Widget->SetSize(Width, Height);

		if (!Widget->Init())
		{
			SAFE_DELETE(Widget);
			return nullptr;
		}

		m_vecWidget.push_back(Widget);

		return Widget;
	}

	template <typename T>
	T* AddPopupWidget(const std::string& Name, float Width = 100.f, float Height = 100.f)
	{
		T* Widget = DBG_NEW T;

		Widget->SetName(Name);
		Widget->SetOwner(this);
		Widget->SetSize(Width, Height);

		if (!Widget->Init())
		{
			SAFE_DELETE(Widget);
			return nullptr;
		}

		m_vecPopupWidget.push_back(Widget);

		return Widget;
	}
};

