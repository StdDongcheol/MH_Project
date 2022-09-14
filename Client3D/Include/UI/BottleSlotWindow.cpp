
#include "BottleSlotWindow.h"
#include "Engine.h"
#include "Input.h"
#include "Widget/Image.h"
#include "Widget/Text.h"
#include "Scene/Viewport.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "../Object/Player.h"

CBottleSlotWindow::CBottleSlotWindow() :
	m_Slot{}
{
	SetTypeID<CBottleSlotWindow>();
}

CBottleSlotWindow::~CBottleSlotWindow()
{
	SAFE_DELETE_ARRAY(m_Slot);
}

void CBottleSlotWindow::SetUsingBottle(bool bEnable)
{
	m_UsedBottleImage->Enable(bEnable);
	m_UsedBottleFrameImage->Enable(bEnable);
	m_UsedBottleFlashImage->Enable(bEnable);
	m_SelectedBackImage->Enable(bEnable);

	if (bEnable)
	{
		m_Slot[1].Text->SetColor(Vector4(0.71f, 1.f, 0.f, 1.f));
	}

	else
	{
		m_Slot[1].Text->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.f));
	}
}

Coating_State CBottleSlotWindow::UsingBottle(bool bEnable)
{
	Coating_State State = m_Slot[1].GetState();

	// �ٸ����ú��̰ų� None �����϶�,
	if (m_CurrentState != State)
	{
		m_CurrentState = State;

		SetUsingBottle(true);

		CheckUsedBottle();
	}

	// ���� ���� ���̾�����,
	else
	{
		// ���� ����.
		m_CurrentState = Coating_State::None;

		SetUsingBottle(false);

		CheckUsedBottle();
	}

	return m_CurrentState;
}

void CBottleSlotWindow::Start()
{
	CWidgetWindow::Start();

	m_Player = (CPlayer*)GetViewport()->GetScene()->GetPlayerObject();
}

bool CBottleSlotWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(500.f, 200.f);

	Resolution RS = CEngine::GetInst()->GetRS();

	Vector2 vectorRS = Vector2((float)RS.Width, (float)RS.Height);

	SetSize(300.f, 100.f);
	// Window�� Width Size�� �׻� ������ķ� �����ֵ���.
	SetPos(vectorRS.x / 2.f + 250.f, vectorRS.y / 2.f - 200.f);

	SetZOrder(2);


	CreateWidgets(GetWindowSize());

	CInput::GetInst()->SetKeyCallback<CBottleSlotWindow>("Up", Key_State::KeyState_Down, this, &CBottleSlotWindow::AscendSlot);
	CInput::GetInst()->SetKeyCallback<CBottleSlotWindow>("Down", Key_State::KeyState_Down, this, &CBottleSlotWindow::DescendSlot);

	return true;
}

void CBottleSlotWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CBottleSlotWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CBottleSlotWindow::Render()
{
	CWidgetWindow::Render();
}

void CBottleSlotWindow::CreateWidgets(Vector2 WindowSize)
{
	m_WindowFrame = CreateWidget<CImage>("WindowFrameImage");
	m_SelectedBackImage = CreateWidget<CImage>("SelectedBackImage");
	m_UsedBottleImage = CreateWidget<CImage>("UsedBottleImage");
	m_UsedBottleFrameImage = CreateWidget<CImage>("UsedBottleFrameImage");
	m_UsedBottleFlashImage = CreateWidget<CImage>("UsedBottleFlashImage");
	
	m_WindowFrame->SetZOrder(1);	
	m_SelectedBackImage->SetZOrder(3);	
	m_UsedBottleImage->SetZOrder(3);	
	m_UsedBottleFrameImage->SetZOrder(1);	
	m_UsedBottleFlashImage->SetZOrder(2);

	m_WindowFrame->SetPos(WindowSize.x / 2.f - 75.f, WindowSize.y / 2.f - 25.f);
	m_UsedBottleFrameImage->SetPos(m_WindowFrame->GetWindowPos().x - 50.f, m_WindowFrame->GetWindowPos().y + 32.f);
	m_UsedBottleImage->SetPos(m_UsedBottleFrameImage->GetWindowPos().x + 13.f, m_UsedBottleFrameImage->GetWindowPos().y + 5.f);
	m_UsedBottleFlashImage->SetPos(m_UsedBottleImage->GetWindowPos());
	
	m_WindowFrame->SetSize(250.f, 100.f);	
	m_SelectedBackImage->SetSize(200.f, 25.f);
	m_UsedBottleImage->SetSize(15.f, 27.f);	
	m_UsedBottleFrameImage->SetSize(40.f, 40.f);	
	m_UsedBottleFlashImage->SetSize(16.f, 28.f);
	
	m_WindowFrame->SetTexture("BottleBaseImage", TEXT("UI/HUD/BottleListBase.png"));	
	m_SelectedBackImage->SetTexture("BottleFocusBack", TEXT("UI/HUD/FocusBackImage.png"));
	m_UsedBottleImage->SetTexture("BottleIconImage", TEXT("UI/HUD/BottleIcon.png"));
	m_UsedBottleFrameImage->SetTexture("BottleFrame", TEXT("UI/HUD/BottleSelected.png"));
	m_UsedBottleFlashImage->SetTexture("BottleFlash", TEXT("UI/HUD/BottleFadeFocus.png"));

	m_SelectedBackImage->SetTextureTint(Vector4(1.f, 5.f, 1.f, 1.f));
	m_UsedBottleImage->SetTextureTint(Vector4(1.f, 0.79f, 0.f, 1.f));
	m_UsedBottleFlashImage->SetTextureTint(Vector4(1.f, 0.89f, 0.f, 0.5f));

	m_UsedBottleFlashImage->SetDuration(0.1f);
	m_UsedBottleFlashImage->SetFadeInTime(0.2f);
	m_UsedBottleFlashImage->SetFadeOutTime(0.2f);
	m_UsedBottleFlashImage->SetFadeLoop(true);

	m_Slot = new BottleSlot[3];

	for (int i = 0; i < 3; ++i)
	{
		m_Slot[i].Image = CreateWidget<CImage>("Icon");
		m_Slot[i].Text = CreateWidget<CText>("Text");
		
		m_Slot[i].Image->SetSize(15.f, 27.f);
		m_Slot[i].Image->SetZOrder(4);
		m_Slot[i].Image->SetTexture("BottleIconImage", TEXT("UI/HUD/BottleIcon.png"));

		m_Slot[i].Text->SetSize(130.f, 30.f);
		m_Slot[i].Text->SetZOrder(4);
		m_Slot[i].Text->SetAlignH(TEXT_ALIGN_H::Left);
		m_Slot[i].Text->SetAlignV(TEXT_ALIGN_V::Middle);
		m_Slot[i].Text->SetAlphaEnable(true);
		m_Slot[i].Text->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.5f));
		m_Slot[i].Text->SetFontSize(20.f);

		// �� ���� �ʱ�ȭ.
		switch (i)
		{
			case 0:
				m_Slot[i].SetTextureTint(Vector4().Red);
				m_Slot[i].SetText(TEXT("���ݺ�"));
				m_Slot[i].Image->SetPos(110.f, 96.f);
				m_Slot[i].CoatingState = Coating_State::Strong;
				break;
			case 1:
				m_Slot[i].SetTextureTint(Vector4().White);
				m_Slot[i].SetText(TEXT("���ݺ�"));
				m_Slot[i].Image->SetPos(97.f, 63.f);
				m_Slot[i].CoatingState = Coating_State::Normal;
				break;
			case 2:
				m_Slot[i].SetTextureTint(Vector4(0.94f, 1.f, 0.25f, 1.f));
				m_Slot[i].SetText(TEXT("���ĺ�"));
				m_Slot[i].Image->SetPos(110.f, 27.f);
				m_Slot[i].CoatingState = Coating_State::Explosion;
				break;
		}

		m_Slot[i].Text->SetPos(m_Slot[i].Image->GetWindowPos().x + 30.f, 
			m_Slot[i].Image->GetWindowPos().y - 2.f);
	}

	m_SelectedBackImage->SetPos(
		m_Slot[1].Image->GetWindowPos().x,
		m_Slot[1].Image->GetWindowPos().y);
	
	SetUsingBottle(false);
}

void CBottleSlotWindow::AscendSlot()
{
	/// <summary>
	/// Player�� ������ϰ�� ��� ��������� Ȯ�ΰ����ϵ���.
	/// Ȯ�εɰ�� �ش� ���Գ� m_SelectedBackImage EnableȮ��.
	/// ������ε� �ٸ� �� ����Ұ�� �ش� ���������ʿ�
	/// </summary>
	

	Vector4 TintVal = Vector4().Black;
	TCHAR* Text = new TCHAR[32];
	Coating_State State = {};

	for (int i = 0; i < 2; ++i)
	{
		TintVal = m_Slot[i + 1].GetTextureTint();
		lstrcpy(Text, m_Slot[i + 1].GetText());
		State = m_Slot[i + 1].CoatingState;

		m_Slot[i + 1].SetTextureTint(m_Slot[i].GetTextureTint());
		m_Slot[i + 1].SetText(m_Slot[i].GetText());
		m_Slot[i + 1].CoatingState = m_Slot[i].CoatingState;

		m_Slot[i].SetTextureTint(TintVal);
		m_Slot[i].SetText(Text);
		m_Slot[i].CoatingState = State;
	}

	for (int i = 0; i < 3; ++i)
	{
		if (i == 1)
		{
			m_Slot[i].Text->SetFontSize(20.f);
			//m_Slot[i].Text->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.f));
			m_Slot[i].Text->SetOpacity(1.f);
		}

		else
		{
			m_Slot[i].Text->SetFontSize(17.f);
			//m_Slot[i].Text->SetColor(Vector4(0.9f, 0.9f, 0.9f, 0.2f));
			m_Slot[i].Text->SetOpacity(0.3f);
		}
	}

	CheckUsedBottle();

	GetViewport()->GetScene()->GetResource()->SoundPlay("BottleSwap");

	SAFE_DELETE_ARRAY(Text);
}

void CBottleSlotWindow::DescendSlot()
{
	Vector4 TintVal = Vector4().Black;
	TCHAR* Text = new TCHAR[32];
	Coating_State State = {};

	for (int i = 2; i > 0; --i)
	{
		TintVal = m_Slot[i - 1].GetTextureTint();
		lstrcpy(Text, m_Slot[i - 1].GetText());
		State = m_Slot[i - 1].CoatingState;

		m_Slot[i - 1].SetTextureTint(m_Slot[i].GetTextureTint());
		m_Slot[i - 1].SetText(m_Slot[i].GetText());
		m_Slot[i - 1].CoatingState = m_Slot[i].CoatingState;

		m_Slot[i].SetTextureTint(TintVal);
		m_Slot[i].SetText(Text);
		m_Slot[i].CoatingState = State;
	}

	for (int i = 0; i < 3; ++i)
	{
		if (i == 1)
		{
			m_Slot[i].Text->SetFontSize(20.f);
			m_Slot[i].Text->SetOpacity(1.f);
			m_SelectedBackImage->Enable(false);
		}

		else
		{
			m_Slot[i].Text->SetFontSize(17.f);
			m_Slot[i].Text->SetOpacity(0.3f);
		}
	}

	CheckUsedBottle();

	GetViewport()->GetScene()->GetResource()->SoundPlay("BottleSwap");

	SAFE_DELETE_ARRAY(Text);
}

void CBottleSlotWindow::CheckUsedBottle()
{
	if (m_CurrentState == Coating_State::None)
	{
		m_SelectedBackImage->Enable(false);

		return;
	}

	for (int i = 0; i < 3; ++i)
	{
		// ������ ���û��¿� ���� ���ý��԰� ������ �����ϰ��
		if (m_Slot[i].CoatingState == m_CurrentState)
		{
			// ��� �������� �������
			if (i == 1)
			{
				m_Slot[i].Text->SetColor(Vector4(0.71f, 1.f, 0.f, 1.f));
				m_SelectedBackImage->Enable(true);
			}

			// �ٸ� �����̶��
			else
			{
				m_Slot[i].Text->SetColor(Vector4(0.71f, 1.f, 0.f, 0.5f));
				m_SelectedBackImage->Enable(false);
			}

			// ���� ���󺯰�
			m_Slot[i].Text->SetColor(Vector4(0.71f, 1.f, 0.f, 1.f));

			// ������ �̵������Ƿ� Ȱ��ȭ ������ �ش� ��ġ�� �Ű�����Ѵ�
			Vector2 Pos = m_Slot[i].Image->GetWindowPos();

			m_UsedBottleFrameImage->SetPos(Pos.x - 60.f, Pos.y - 5.f);	
			m_UsedBottleImage->SetPos(m_UsedBottleFrameImage->GetWindowPos().x + 13.f, m_UsedBottleFrameImage->GetWindowPos().y + 5.f);
			m_UsedBottleFlashImage->SetPos(m_UsedBottleImage->GetWindowPos());
		}

		// ���� ���û��°� None�̸�,
		else
		{
			// ��� �����̶�� ���.
			if (i == 1)
				m_Slot[i].Text->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.f));

			// �׿� ������ ��Ӱ�.
			else
				m_Slot[i].Text->SetColor(Vector4(0.9f, 0.9f, 0.9f, 0.2f));
		}
	}

}
