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
	Text->SetText("F1 : 카메라 토글\nF2 : 충돌체 렌더링 ON/OFF\nF3 : 오브젝트 생성\nF4 : 오브젝트 삭제\nF12 : 에디터 종료\nW, A, S, D, Q, E : 카메라 이동\n좌클릭, 우클릭 : 지형 쌓기, 파내기\n휠업, 휠다운 : 지형 브러쉬 범위 조절\nESC : 오브젝트 선택 취소");

	return true;
}
