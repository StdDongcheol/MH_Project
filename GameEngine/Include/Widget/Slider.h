
#pragma once

#include "Widget.h"

class CSlider :
	public CWidget
{
	friend class CWidgetWindow;

protected:
	CSlider();
	CSlider(const CSlider& widget);
	virtual ~CSlider();

protected:
	
	WidgetImageInfo	m_Info;
	std::function<void()>	m_ClickCallback;
	Vector2 PreMousePos;
	Vector2 CurrentMousePos;
	Vector2 PreSliderPos;
	float MinX;
	float MaxX;

public:
	void SetMinMax(float Min, float Max)
	{
		MinX = Min;
		MaxX = Max;
	}

	virtual void Enable(bool bEnable)
	{
		CWidget::Enable(bEnable);
	}



	void SetTexture(CTexture* Texture)
	{
		m_Info.Texture = Texture;

		SetUseTexture(true);
	}

	bool SetTexture(const std::string& Name, const TCHAR* FileName,	const std::string& PathName = TEXTURE_PATH);
	bool SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	void SetTextureTint(const Vector4& Tint);
	void SetTextureTint(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void AddFrameData(const Vector2& Start, const Vector2& Size);
	void SetPlayTime(float PlayTime);
	void SetPlayScale(float PlayScale);


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CSlider* Clone();

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

