#include "AboutWindow.h"
#include "IMGUIText.h"

CAboutWindow::CAboutWindow()
{
}

CAboutWindow::~CAboutWindow()
{
}

bool CAboutWindow::Init()
{
	CIMGUIText* Text = nullptr;

	Text = AddWidget<CIMGUIText>("Text");
	Text->SetText("F1 : ī�޶� ���\nF2 : �浹ü ������ ON/OFF\nF3 : ������Ʈ ����\nF4 : ������Ʈ ����\nF12 : ������ ����\nW, A, S, D, Q, E : ī�޶� �̵�\n��Ŭ��, ��Ŭ�� : ���� �ױ�, �ĳ���\n�پ�, �ٴٿ� : ���� �귯�� ���� ����\nESC : ������Ʈ ���� ���");

	return true;
}
