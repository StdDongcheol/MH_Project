
#include "EditorScene.h"
#include "Scene/Scene.h"

void CEditorScene::LoadFieldObj()
{
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallTree1", TEXT("Object/SmallTree1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallTree2", TEXT("Object/SmallTree2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallTree3", TEXT("Object/SmallTree3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallTree4", TEXT("Object/SmallTree4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallTree5", TEXT("Object/SmallTree5.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree1", TEXT("Object/Tree1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree2", TEXT("Object/Tree2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree3", TEXT("Object/Tree3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree4", TEXT("Object/Tree4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree5", TEXT("Object/Tree5.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree6", TEXT("Object/Tree6.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree7", TEXT("Object/Tree7.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree8", TEXT("Object/Tree8.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree9", TEXT("Object/Tree9.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BigTree1", TEXT("Object/BigTree1.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BrokenTree1", TEXT("Object/BrokenTree1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BrokenTree2", TEXT("Object/BrokenTree2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BrokenTree3", TEXT("Object/BrokenTree3.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "MushRoom1", TEXT("Object/Mushroom1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "MushRoom2", TEXT("Object/Mushroom2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "MushRoom3", TEXT("Object/Mushroom3.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass1", TEXT("Object/Grass1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass2", TEXT("Object/Grass2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass3", TEXT("Object/Grass3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass4", TEXT("Object/Grass4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass5", TEXT("Object/Grass5.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass6", TEXT("Object/Grass6.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass7", TEXT("Object/Grass7.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass8", TEXT("Object/Grass8.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass9", TEXT("Object/Grass9.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass10", TEXT("Object/Grass10.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallGrass", TEXT("Object/SmallGrass.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallStone1", TEXT("Object/SmallStone1.msh"));

	// 바위 (이끼바위)
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock1", TEXT("Object/GrassRock1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock2", TEXT("Object/GrassRock2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock3", TEXT("Object/GrassRock3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock4", TEXT("Object/GrassRock4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock5", TEXT("Object/GrassRock5.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock6", TEXT("Object/GrassRock6.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock7", TEXT("Object/GrassRock7.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock8", TEXT("Object/GrassRock8.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock9", TEXT("Object/GrassRock9.msh"));


	// 건축물 (텐트)
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tent1", TEXT("Object/Tent1.msh")); // 야영 텐트
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tent2", TEXT("Object/Tent2.msh"));	// 마을용 텐트

	// 건축물 (상자박스)
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Box1", TEXT("Object/Box1.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Precipice1", TEXT("Object/Precipice1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Precipice2", TEXT("Object/Precipice2.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Sculpture1", TEXT("Object/Sculpture1.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Vine", TEXT("Object/Vine.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Vine2", TEXT("Object/Vine2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Vine3", TEXT("Object/Vine3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Vine4", TEXT("Object/Vine4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Vine5", TEXT("Object/Vine5.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Wreck", TEXT("Object/Wreck.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Wreck1", TEXT("Object/Wreck1.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Far", TEXT("Object/Far.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertBigStone1", TEXT("DesertObj/DesertBigStone1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertPebble1", TEXT("DesertObj/DesertPebble1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertRockWall", TEXT("DesertObj/DesertRockWall.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertSmallStone1", TEXT("DesertObj/DesertSmallStone1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalactite1", TEXT("DesertObj/DesertStalactite1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalactite2", TEXT("DesertObj/DesertStalactite2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalactite3", TEXT("DesertObj/DesertStalactite3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalactite4", TEXT("DesertObj/DesertStalactite4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalagmite1", TEXT("DesertObj/DesertStalagmite1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalagmite2", TEXT("DesertObj/DesertStalagmite2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalagmite3", TEXT("DesertObj/DesertStalagmite3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone1", TEXT("DesertObj/DesertStone1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone2", TEXT("DesertObj/DesertStone2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone3", TEXT("DesertObj/DesertStone3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone4", TEXT("DesertObj/DesertStone4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone5", TEXT("DesertObj/DesertStone5.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone6", TEXT("DesertObj/DesertStone6.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej1", TEXT("stonej/stonej1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej2", TEXT("stonej/stonej2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej3", TEXT("stonej/stonej3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej4", TEXT("stonej/stonej4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej5", TEXT("stonej/stonej5.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej6", TEXT("stonej/stonej6.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej7", TEXT("stonej/stonej7.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej8", TEXT("stonej/stonej8.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej9", TEXT("stonej/stonej9.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej10", TEXT("stonej/stonej10.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej11", TEXT("stonej/stonej11.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej12", TEXT("stonej/stonej12.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej13", TEXT("stonej/stonej13.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej14", TEXT("stonej/stonej14.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej15", TEXT("stonej/stonej15.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej16", TEXT("stonej/stonej16.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej17", TEXT("stonej/stonej17.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej18", TEXT("stonej/stonej18.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej19", TEXT("stonej/stonej19.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej20", TEXT("stonej/stonej20.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej21", TEXT("stonej/stonej21.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej22", TEXT("stonej/stonej22.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej23", TEXT("stonej/stonej23.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej24", TEXT("stonej/stonej24.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej25", TEXT("stonej/stonej25.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej26", TEXT("stonej/stonej26.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej27", TEXT("stonej/stonej27.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej28", TEXT("stonej/stonej28.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej29", TEXT("stonej/stonej29.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej30", TEXT("stonej/stonej30.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej31", TEXT("stonej/stonej31.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej32", TEXT("stonej/stonej32.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej33", TEXT("stonej/stonej33.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej34", TEXT("stonej/stonej34.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej35", TEXT("stonej/stonej35.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej36", TEXT("stonej/stonej36.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej37", TEXT("stonej/stonej37.msh"));

	//Town
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownBarrel", TEXT("TownObj/TownBarrel.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownCarriage", TEXT("TownObj/TownCarriage.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownCheckPoint", TEXT("TownObj/TownCheckPoint.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownDragonHead", TEXT("TownObj/TownDragonHead.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownPassage", TEXT("TownObj/TownPassage.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownPumpkinMan", TEXT("TownObj/TownPumpkinMan.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownRampart", TEXT("TownObj/TownRampart.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownShadeScreen", TEXT("TownObj/TownShadeScreen.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownSign", TEXT("TownObj/TownSign.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownStructure", TEXT("TownObj/TownStructure.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownSummerHouse", TEXT("TownObj/TownSummerHouse.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownTunnel", TEXT("TownObj/TownTunnel.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertMountain1", TEXT("DesertObj/DesertMountain1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertMountain2", TEXT("DesertObj/DesertMountain2.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Blank", TEXT("Object/Blank.msh"));
}
