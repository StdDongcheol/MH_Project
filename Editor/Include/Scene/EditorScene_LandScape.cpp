
#include "EditorScene.h"
#include "Scene/Scene.h"

void CEditorScene::LoadLandScape()
{
	m_Scene->GetResource()->CreateMaterial<CMaterial>("LandScape");

	CMaterial* Material = m_Scene->GetResource()->FindMaterial("LandScape");

	Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "LandScapeSplat1Dif", TEXT("LandScape/Sand/0_BML.dds"));
	Material->AddTexture(1, (int)Buffer_Shader_Type::Pixel, "LandScapeSplat1Nrm", TEXT("LandScape/Sand/0_NM.dds"));

	std::vector<TCHAR*>	vecSPLTexture, vecSPLNormal;

	vecSPLTexture.reserve(12);
	vecSPLNormal.reserve(12);

	AddLandScape(vecSPLTexture, TEXT("LandScape/Grass/1_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Grass/2_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Grass/3_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Grass/4_BML.dds"));

	AddLandScape(vecSPLNormal, TEXT("LandScape/Grass/1_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Grass/2_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Grass/3_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Grass/4_NM.dds"));


	AddLandScape(vecSPLTexture, TEXT("LandScape/Sand/1_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Sand/2_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Sand/3_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Sand/4_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Sand/5_BML.dds"));

	AddLandScape(vecSPLNormal, TEXT("LandScape/Sand/1_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Sand/2_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Sand/3_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Sand/4_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Sand/5_NM.dds"));


	AddLandScape(vecSPLTexture, TEXT("LandScape/Rock/1_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Rock/2_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Rock/3_BML.dds"));

	AddLandScape(vecSPLNormal, TEXT("LandScape/Rock/1_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Rock/2_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Rock/3_NM.dds"));


	SetLandScape(34, "SPLTexture", vecSPLTexture);
	SetLandScape(35, "SPLNormal", vecSPLNormal);

	Material->SetShader("LandScapeShader");

	Material->EnableBump();
	Material->EnableSpecularTex();
	Material->SetSpecularPower(2.5f);
}