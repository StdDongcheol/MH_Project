
#include "MaterialManager.h"
#include "../ResourceManager.h"
#include "../Shader/MaterialConstantBuffer.h"

CMaterialManager::CMaterialManager()	:
	m_CBuffer(nullptr)
{
}

CMaterialManager::~CMaterialManager()
{
	SAFE_DELETE(m_CBuffer);
}

bool CMaterialManager::Init()
{
	m_CBuffer = new CMaterialConstantBuffer;

	m_CBuffer->Init();

	CreateMaterial<CMaterial>("Color");

	CSharedPtr<CMaterial>	Mtrl = FindMaterial("Color");

	Mtrl->SetShader("ColorMeshShader");

	CreateMaterial<CMaterial>("BaseTexture");

	Mtrl = FindMaterial("BaseTexture");

	Mtrl->SetShader("Mesh2DShader");

	CTexture* Texture = CResourceManager::GetInst()->FindTexture("EngineTexture");

	Mtrl->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "EngineTexture", Texture);

	CreateMaterial<CMaterial>("SkyMaterial");

	Mtrl = FindMaterial("SkyMaterial");

	Mtrl->SetShader("SkyShader");

	Mtrl->AddTexture(20, (int)Buffer_Shader_Type::Pixel, "DefaultSky", TEXT("Sky/Sky.dds"));

	CreateMaterial<CMaterial>("DefaultDecal");
	Mtrl = FindMaterial("DefaultDecal");
	Mtrl->SetShader("DecalShader");
	Mtrl->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "DefaultDecal", TEXT("Decal.png"));
	Mtrl->SetSpecularColor(Vector4().Black);

	CreateMaterial<CMaterial>("DebugDecal");
	Mtrl = FindMaterial("DebugDecal");
	Mtrl->SetShader("DecalDebugShader");


	CreateMaterial<CMaterial>("Billboard");

	Mtrl = FindMaterial("Billboard");

	Mtrl->SetShader("BillboardShader");

	Texture = CResourceManager::GetInst()->FindTexture("EngineTexture");

	Mtrl->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "EngineTexture", Texture);

	return true;
}

CMaterial* CMaterialManager::FindMaterial(const std::string& Name)
{
	auto	iter = m_mapMaterial.find(Name);

	if (iter == m_mapMaterial.end())
		return nullptr;

	return iter->second;
}

void CMaterialManager::ReleaseMaterial(const std::string& Name)
{
	auto	iter = m_mapMaterial.find(Name);

	if (iter != m_mapMaterial.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapMaterial.erase(iter);
	}
}
