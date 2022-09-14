

#pragma once

#include "Widget.h"

class CCheckBox :
	public CWidget
{
	friend class CWidgetWindow;

protected:
	CCheckBox();
	CCheckBox(const CCheckBox& widget);
	virtual ~CCheckBox();

protected:

	
	WidgetImageInfo Info[2];
	std::function<void()>	m_ClickCallback;	
	bool			m_MouseOnSound;
	bool			m_ClickSound;
	bool IsChecked;

public:
	void SetCheck(bool b)
	{
		IsChecked = b;
	}

	bool GetCheck()
	{
		return IsChecked;
	}




	void SetTexture(bool Checked, CTexture* Texture)
	{
		if (false == Checked)
		{
			Info[0].Texture = Texture;
		}
		else 
		{
			Info[1].Texture = Texture;
		}
		SetUseTexture(true);
	}

	bool SetTexture(bool Checked, const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	bool SetTextureFullPath(bool Checked, const std::string& Name,
		const TCHAR* FullPath);
	void SetTextureTint(bool Checked, const Vector4& Tint);
	void SetTextureTint(bool Checked, unsigned char r, unsigned char g,
		unsigned char b, unsigned char a);



public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CCheckBox* Clone();

public:
	template <typename T>
	void SetClickCallback(T* Obj, void (T::* Func)())
	{
		m_ClickCallback = std::bind(Func, Obj);
	}

	void SetClickCallback(void (*Func)())
	{
		m_ClickCallback = std::bind(Func);
	}
};

