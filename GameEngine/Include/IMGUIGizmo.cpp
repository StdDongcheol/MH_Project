#include "IMGUIGizmo.h"
#include "Component/CameraComponent.h"
#include "GameObject/GameObject.h"
#include "Scene/SceneManager.h"
#include "Input.h"

CIMGUIGizmo::CIMGUIGizmo()	:
	m_TargetOper(ImGuizmo::TRANSLATE),
	m_matCamView{},
	m_matCamProj{},
	m_matTarget{},
	m_CamView{},
	m_CamProj{},
	m_Result{},
	m_Target(nullptr),
	m_Pos{},
	m_Scale{},
	m_Rot{},
	m_PosText{},
	m_ScaleText{},
	m_RotText{},
	m_Check(false)
{
	float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };

	memcpy(&m_Bounds[0], &bounds[0], sizeof(float) * 6);
}

CIMGUIGizmo::~CIMGUIGizmo()
{
}

bool CIMGUIGizmo::Init()
{
	m_Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

	char	Text[5] = {};

	strcpy_s(m_PosText, UTF8("위치"));
	strcpy_s(m_ScaleText, UTF8("크기"));
	strcpy_s(m_RotText, UTF8("회전"));

	return true;
}

bool CIMGUIGizmo::Render()
{
	if (ImGui::RadioButton(m_PosText, m_TargetOper == ImGuizmo::TRANSLATE))
		m_TargetOper = ImGuizmo::TRANSLATE;

	ImGui::SameLine();

	if (ImGui::RadioButton(m_ScaleText, m_TargetOper == ImGuizmo::SCALE))
		m_TargetOper = ImGuizmo::SCALE;

	ImGui::SameLine();

	if (ImGui::RadioButton(m_RotText, m_TargetOper == ImGuizmo::ROTATE))
		m_TargetOper = ImGuizmo::ROTATE;

	if (!CIMGUIWidget::Render())
		return false;

	ImGuizmo::SetOrthographic(false);

	ImGuizmo::BeginFrame();

	MatrixToFloat();
	EditTransform(m_Result);

	return true;
}

bool CIMGUIGizmo::IsUsing() const
{
	return ImGuizmo::IsUsing();
}

bool CIMGUIGizmo::IsHovered() const
{
	return ImGuizmo::IsOver(m_TargetOper);
}

void CIMGUIGizmo::MatrixToFloat()
{
	m_matCamView = m_Camera->GetViewMatrix();
	m_matCamProj = m_Camera->GetProjMatrix();

	for (int i = 0; i < 4; ++i)
	{
		memcpy(&m_CamView[i * 4], &m_matCamView[i][0], sizeof(float) * 16);
		memcpy(&m_CamProj[i * 4], &m_matCamProj[i][0], sizeof(float) * 16);
	}

	if (m_Target && !m_Check)
	{
		m_Check = true;

		m_matTarget = m_Target->GetWorldMatrix();

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m_Result[i * 4 + j] = m_matTarget[i][j];
			}
		}
	}
}

void CIMGUIGizmo::EditTransform(float* matrix)
{
	ImGuizmo::DecomposeMatrixToComponents(matrix, m_Pos, m_Rot, m_Scale);

	ImGuizmo::RecomposeMatrixFromComponents(m_Pos, m_Rot, m_Scale, matrix);

	if (!m_Target)
		return;

	RECT WindowRect = CEngine::GetInst()->GetWindowPos();

	ImGuizmo::SetRect((float)WindowRect.left, (float)WindowRect.top, (float)(WindowRect.right - WindowRect.left), (float)(WindowRect.bottom - WindowRect.top));

	ImGuizmo::Manipulate(m_CamView, m_CamProj, m_TargetOper, ImGuizmo::WORLD, matrix);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_matTarget[i][j] = m_Result[i * 4 + j];
		}
	}
	
	//bool	Using = IsUsing();

	m_Target->SetWorldScale(Vector3(m_Scale[0], m_Scale[1], m_Scale[2]));
	m_Target->SetWorldPos(Vector3(m_Pos[0], m_Pos[1], m_Pos[2]));
	m_Target->SetWorldRot(Vector3(m_Rot[0], m_Rot[1], m_Rot[2]));

	// 테스트 필요
	//m_Target->SetWorldMatrix(m_matTarget);
}