
#include "EditorScene.h"
#include "Scene/Scene.h"
#include "Engine.h"

void CEditorScene::LoadFBX()
{
	bool Use = false;

	//m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Blank", TEXT("Object/Blank.fbx"));

	if (Use)
		CEngine::GetInst()->Exit();
}