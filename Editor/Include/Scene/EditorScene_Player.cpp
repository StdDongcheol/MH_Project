
#include "EditorScene.h"
#include "Scene/Scene.h"

void CEditorScene::LoadPlayer()
{


	// 화살 통
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BowBoxMesh",
		TEXT("BowHunter/Bow/HunterBowBox.msh"));

	// 화살
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "ArrowMesh",
		TEXT("BowHunter/Bow/Arrow.msh"));

	//무기
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "BowMesh",
		TEXT("BowHunter/Bow/BowBody.msh"));

	m_Scene->GetResource()->LoadSkeleton("BowSkeleton",
		TEXT("BowHunter/Bow/BowBody.bne"), MESH_PATH);

	m_Scene->GetResource()->SetMeshSkeleton("BowMesh", "BowSkeleton");

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowBack",
		TEXT("BowHunter/Bow/BowBody.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowOpen",
		TEXT("BowHunter/Bow/sqc/BowOpen.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowClose",
		TEXT("BowHunter/Bow/sqc/BowClose.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowShot",
		TEXT("BowHunter/Bow/sqc/BowShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowChargingLoop",
		TEXT("BowHunter/Bow/sqc/BowChargingLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowChargingStart",
		TEXT("BowHunter/Bow/sqc/BowChargingStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowChargingToIdle",
		TEXT("BowHunter/Bow/sqc/BowChargingToIdle.sqc"), MESH_PATH);

	//플레이어	
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "PlayerMesh",
		TEXT("BowHunter/BodyVer4.msh"));

	m_Scene->GetResource()->LoadSkeleton("PlayerSkeleton",
		TEXT("BowHunter/BodyVer4.bne"), MESH_PATH);

	m_Scene->GetResource()->SetMeshSkeleton("PlayerMesh", "PlayerSkeleton");

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "PlayerFaceMesh",
		TEXT("BowHunter/BowHunterFace.msh"));

	// 시퀀스
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHIdle",
		TEXT("BowHunter/co00/Hunter/HunterIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHWalk",
		TEXT("BowHunter/co00/Hunter/HunterWalkLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHWalkEnd",
		TEXT("BowHunter/co00/Hunter/HunterWalkEnd1.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRunStart",
		TEXT("BowHunter/co00/Hunter/HunterRunStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRun",
		TEXT("BowHunter/co00/Hunter/HunterRunLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRunQuick",
		TEXT("BowHunter/co00/Hunter/HunterRunQuickLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRunEnd",
		TEXT("BowHunter/co00/Hunter/HunterRunEnd1.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHEvade",
		TEXT("BowHunter/co00/Hunter/HunterEvade.sqc"), MESH_PATH);



	//wp
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHKick",
		TEXT("BowHunter/co00/Hunter/wp/HunterArcShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterArcShot.sqc"), MESH_PATH);

	// AimCharging
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimChargingWalkFront",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimChargingWalkFront.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimChargingWalkBack",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimChargingWalkBack.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimChargingWalkLeft",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimChargingWalkLeft.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimChargingWalkRight",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimChargingWalkRight.sqc"), MESH_PATH);

	// Aim
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimIdleToSlingerAim",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimIdleToDrawnSlingerAim.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimIdleToIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimIdleToIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimLoopArcShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimLoopArcShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimStartArcShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimStartArcShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkFront",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkFront.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkBack",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkBack.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkLeft",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkLeft.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkLeftEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkLeftEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkRight",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkRight.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkRightEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkRightEnd.sqc"), MESH_PATH);

	// Charging
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargedShotIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargedShotIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingFrontStep",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingFrontStep.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingFrontStepShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingFrontStepShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingIdleToChargingWalk",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingIdleToChargingWalk.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingLeftStep",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingLeftStep.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingLeftStepShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingLeftStepShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingRightStep",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingRightStep.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingRightStepShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingRightStepShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingStartIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingStartIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingStartIdleFirst",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingStartIdleFirst.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingWalk",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingWalk.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingWalkEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingWalkEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingWalkLeftEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingWalkLeftEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingWalkRightEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingWalkRightEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHFullChargingIdleLoop",
		TEXT("BowHunter/co00/Hunter/wp/HunterFullChargingIdleLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHFullChargedShotIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterFullChargedShotIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHPowerShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterPowerShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHQuickShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterQuickShot.sqc"), MESH_PATH);

	// Drawed
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedBackStep",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedBackStep.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedEvade",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedEvade.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedEvadeToDrawedWalkStart",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedEvadeToDrawedWalkStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedEvadeToDrawedWalk",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedEvadeToDrawedWalk.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedWalk",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedWalk.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedWalkAndSheathe",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedWalkAndSheathe.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedWalkEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedWalkEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedWalkStart",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedWalkStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedWeaponToCharging",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedWeaponToCharging.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedToChargingStart",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedToChargingStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawnEvadeFront",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawnEvadeFront.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawnHitFront",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawnHitFront.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawWeapon",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawWeapon.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHWalkAndDrawWeapon",
		TEXT("BowHunter/co00/Hunter/wp/HunterWalkAndDrawWeapon.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawnWalkToChargingStart",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawnWalkToChargingStart.sqc"), MESH_PATH);

	// BowSheathe
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHSheathe",
		TEXT("BowHunter/co00/Hunter/wp/HunterSheathe.sqc"), MESH_PATH);
	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone100",
		"BowHead");
	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone11",
		"BowLeftHand");
	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone46",
		"BowRightHand");

	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone75",
		"BackBow");


	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "boneWst10",
		"BowBox");

	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone6",
		"PlayerFace");

	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone0",
		"HitBreath");

	m_Scene->GetResource()->AddSocket("BowSkeleton", "BoneFunction.100",
		"BowVfx");
}