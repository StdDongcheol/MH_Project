
#include "EditorScene.h"
#include "Scene/Scene.h"

void CEditorScene::LoadMonster()
{
	//vespoid
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "VespoidMesh", TEXT("vespoid/vespoidmain.msh"));

	m_Scene->GetResource()->LoadSkeleton("VespoidSkeleton", TEXT("vespoid/vespoidmain.bne"), MESH_PATH);

	m_Scene->GetResource()->SetMeshSkeleton("VespoidMesh", "VespoidSkeleton");

	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid1", TEXT("vespoid/vespoid1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid2", TEXT("vespoid/vespoid2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid3", TEXT("vespoid/vespoid3.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid4", TEXT("vespoid/vespoid4.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid5", TEXT("vespoid/vespoid5.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid6", TEXT("vespoid/vespoid6.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid7", TEXT("vespoid/vespoid7.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid8", TEXT("vespoid/vespoid8.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid9", TEXT("vespoid/vespoid9.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid10", TEXT("vespoid/vespoid10.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid11", TEXT("vespoid/vespoid11.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid12", TEXT("vespoid/vespoid12.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid13", TEXT("vespoid/vespoid13.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid14", TEXT("vespoid/vespoid14.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid15", TEXT("vespoid/vespoid15.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid16", TEXT("vespoid/vespoid16.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid17", TEXT("vespoid/vespoid17.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid18", TEXT("vespoid/vespoid18.sqc"), MESH_PATH);

	//barnos
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "BarnosMesh", TEXT("barnos/barnosmain.msh"));

	m_Scene->GetResource()->LoadSkeleton("BarnosSkeleton", TEXT("barnos/barnosmain.bne"), MESH_PATH);

	m_Scene->GetResource()->SetMeshSkeleton("BarnosMesh", "BarnosSkeleton");

	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos1", TEXT("barnos/barnos1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos2", TEXT("barnos/barnos2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos3", TEXT("barnos/barnos3.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos4", TEXT("barnos/barnos4.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos5", TEXT("barnos/barnos5.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos6", TEXT("barnos/barnos6.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos7", TEXT("barnos/barnos7.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos8", TEXT("barnos/barnos8.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos9", TEXT("barnos/barnos9.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos10", TEXT("barnos/barnos10.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos11", TEXT("barnos/barnos11.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos12", TEXT("barnos/barnos12.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos13", TEXT("barnos/barnos13.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos14", TEXT("barnos/barnos14.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos15", TEXT("barnos/barnos15.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos16", TEXT("barnos/barnos16.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos17", TEXT("barnos/barnos17.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos18", TEXT("barnos/barnos18.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos19", TEXT("barnos/barnos19.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "barnosmain", TEXT("barnos/barnosmain.sqc"), MESH_PATH);

	//jagras
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "JagrasMesh", TEXT("jagras/jagrasmain.msh"));

	m_Scene->GetResource()->LoadSkeleton("JagrasSkeleton", TEXT("jagras/jagrasmain.bne"), MESH_PATH);

	m_Scene->GetResource()->SetMeshSkeleton("JagrasMesh", "JagrasSkeleton");

	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras1", TEXT("jagras/jagras1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras2", TEXT("jagras/jagras2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras3", TEXT("jagras/jagras3.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras4", TEXT("jagras/jagras4.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras5", TEXT("jagras/jagras5.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras6", TEXT("jagras/jagras6.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras7", TEXT("jagras/jagras7.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras8", TEXT("jagras/jagras8.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras9", TEXT("jagras/jagras9.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras10", TEXT("jagras/jagras10.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras11", TEXT("jagras/jagras11.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras12", TEXT("jagras/jagras12.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras13", TEXT("jagras/jagras13.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras14", TEXT("jagras/jagras14.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras15", TEXT("jagras/jagras15.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras16", TEXT("jagras/jagras16.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras17", TEXT("jagras/jagras17.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras18", TEXT("jagras/jagras18.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras19", TEXT("jagras/jagras19.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras20", TEXT("jagras/jagras20.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras21", TEXT("jagras/jagras21.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras22", TEXT("jagras/jagras22.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras23", TEXT("jagras/jagras23.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras24", TEXT("jagras/jagras24.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras25", TEXT("jagras/jagras25.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras26", TEXT("jagras/jagras26.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras27", TEXT("jagras/jagras27.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras28", TEXT("jagras/jagras28.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras29", TEXT("jagras/jagras29.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras30", TEXT("jagras/jagras30.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras31", TEXT("jagras/jagras31.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras32", TEXT("jagras/jagras32.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras33", TEXT("jagras/jagras33.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras34", TEXT("jagras/jagras34.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "jagrasmain", TEXT("jagras/jagrasmain.sqc"), MESH_PATH);


	//kestodon
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "KestodonMesh", TEXT("kestodon/kestodonmain.msh"));

	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon1", TEXT("kestodon/kestodon1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon2", TEXT("kestodon/kestodon2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon3", TEXT("kestodon/kestodon3.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon4", TEXT("kestodon/kestodon4.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon5", TEXT("kestodon/kestodon5.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon6", TEXT("kestodon/kestodon6.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon7", TEXT("kestodon/kestodon7.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon8", TEXT("kestodon/kestodon8.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon9", TEXT("kestodon/kestodon9.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon10", TEXT("kestodon/kestodon10.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon11", TEXT("kestodon/kestodon11.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon12", TEXT("kestodon/kestodon12.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon13", TEXT("kestodon/kestodon13.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon14", TEXT("kestodon/kestodon14.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon15", TEXT("kestodon/kestodon15.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon16", TEXT("kestodon/kestodon16.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon17", TEXT("kestodon/kestodon17.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon18", TEXT("kestodon/kestodon18.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon19", TEXT("kestodon/kestodon19.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon20", TEXT("kestodon/kestodon20.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon21", TEXT("kestodon/kestodon21.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon22", TEXT("kestodon/kestodon22.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon23", TEXT("kestodon/kestodon23.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon24", TEXT("kestodon/kestodon24.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon25", TEXT("kestodon/kestodon25.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon26", TEXT("kestodon/kestodon26.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon27", TEXT("kestodon/kestodon27.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon28", TEXT("kestodon/kestodon28.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon29", TEXT("kestodon/kestodon29.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadSkeleton("KestodonSkeleton", TEXT("kestodon/kestodonmain.bne"), MESH_PATH);

	m_Scene->GetResource()->SetMeshSkeleton("KestodonMesh", "KestodonSkeleton");

	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodonmain", TEXT("kestodon/kestodonmain.sqc"), MESH_PATH);


	// Anjanath (안자냐프)
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "AnjanathMesh", TEXT("Boss/Anjanath/Anjanath.msh"));

	m_Scene->GetResource()->LoadSkeleton("AnjanathSkeleton", TEXT("Boss/Anjanath/EM100_Anjanath.bne"), MESH_PATH);

	m_Scene->GetResource()->SetMeshSkeleton("AnjanathMesh", "AnjanathSkeleton");

	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalIdle", TEXT("Boss/Anjanath/em100_05_01_NormalIdle.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalMoveStart", TEXT("Boss/Anjanath/EM100_NormalMoveStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalMoveLoop", TEXT("Boss/Anjanath/EM100_NormalMoveLoop_V2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalMoveEnd", TEXT("Boss/Anjanath/EM100_NormalMoveEnd_V3.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalTurnLeft", TEXT("Boss/Anjanath/EM100_NormalTurnLeft.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalTurnRight", TEXT("Boss/Anjanath/EM100_NormalTurnRight.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalTurnBack", TEXT("Boss/Anjanath/EM100_NormalTurnBackToLeft.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathRoaring", TEXT("Boss/Anjanath/EM100_NormalStateRoaring.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAgressiveIdle", TEXT("Boss/Anjanath/EM100_AgressivelIdle.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAgressiveTurnLeft", TEXT("Boss/Anjanath/EM100_AgressiveTurnLeft_NoRot.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAgressiveTurnRight", TEXT("Boss/Anjanath/EM100_AgressiveTurnRight_NoRot.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAgressiveTurnEnd", TEXT("Boss/Anjanath/EM100_AgressiveTurnedEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAttackDashStart", TEXT("Boss/Anjanath/EM100_Attack_DashStart_v1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAttackDashEnd", TEXT("Boss/Anjanath/EM100_Attack_DashEnd_v1.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathTripleBiteStart", TEXT("Boss/Anjanath/EM100_TripleBiteAttack_Start.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathTripleBite1", TEXT("Boss/Anjanath/EM100_TripleBiteAttack_P1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathTripleBite2", TEXT("Boss/Anjanath/EM100_TripleBiteAttack_P2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathTripleBiteV2End", TEXT("Boss/Anjanath/EM100_TripleBiteAttack_End.sqc"), MESH_PATH);

	// Rathalos (리오레우스)
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "RathalosMesh", TEXT("Boss/Rathalos/Rathalos.msh"));
	m_Scene->GetResource()->LoadSkeleton("RathalosSkeleton", TEXT("Boss/Rathalos/Rathalos.bne"), MESH_PATH);
	m_Scene->GetResource()->SetMeshSkeleton("RathalosMesh", "RathalosSkeleton");
	
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosNormalIdle", TEXT("Boss/Rathalos/Rathalos_Idle.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosNormalMoveStart", TEXT("Boss/Rathalos/Rathalos_WalkStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosNormalMoveLoop", TEXT("Boss/Rathalos/Rathalos_WalkLoop.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosRoaring", TEXT("Boss/Rathalos/Rathalos_Roaring.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosBiteStart", TEXT("Boss/Rathalos/Rathalos_BiteStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosBiteEnd", TEXT("Boss/Rathalos/Rathalos_BiteEnd.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosChargeStart", TEXT("Boss/Rathalos/Rathalos_ChargeStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosChargeEnd", TEXT("Boss/Rathalos/Rathalos_ChargeEnd.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosTailSpinAttack", TEXT("Boss/Rathalos/Rathalos_TailSpinAttack.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosAgressiveTurnLeft", TEXT("Boss/Rathalos/Rathalos_AgressiveTurnLeft.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosAgressiveTurnRight", TEXT("Boss/Rathalos/Rathalos_AgressiveTurnRight.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosFlyStart", TEXT("Boss/Rathalos/Rathalos_FlyStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosFlyToIdle", TEXT("Boss/Rathalos/Rathalos_FlyStartToFlyIdle.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosFlyIdle", TEXT("Boss/Rathalos/Rathalos_FlyIdle.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosLandStart", TEXT("Boss/Rathalos/Rathalos_LandingStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosLandEnd", TEXT("Boss/Rathalos/Rathalos_LandEnd.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosFlyBreathStart", TEXT("Boss/Rathalos/Rathalos_FlyBreathStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosFlyBreath", TEXT("Boss/Rathalos/Rathalos_FlyBreath.sqc"), MESH_PATH);

	//바르노스
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.004", "Head");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.102", "Body1");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.100", "Body2");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.002", "Body3");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.141", "Body4");

	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.027", "RightWing1");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.234", "RightWing2");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.180", "RightWing3");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.181", "RightWing4");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.173", "RightWing5");

	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.023", "LeftWing1");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.214", "LeftWing2");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.159", "LeftWing3");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.161", "LeftWing4");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.153", "LeftWing5");




	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.090", "RightFoot");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.080", "LeftFoot");

	//랑고스타
	m_Scene->GetResource()->AddSocket("VespoidSkeleton", "BoneFunction.000", "UpperBody");
	m_Scene->GetResource()->AddSocket("VespoidSkeleton", "BoneFunction.141", "LowerBody");
	m_Scene->GetResource()->AddSocket("VespoidSkeleton", "BoneFunction.142", "Attack");

	//자그라스
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.121", "Head");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.101", "Body1");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.100", "Body2");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.002", "Body3");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.000", "Body4");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.140", "Body5");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.141", "Tail1");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.142", "Tail2");

	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.040", "LeftFoot");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.060", "RightFoot");

	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.012", "RightFrontLeg");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.008", "LeftFrontLeg");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.019", "RightBackLeg");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.015", "LeftBackLeg");

	//케스토톤
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.003", "Head");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.002", "UpperBody");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.140", "LowerBody");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.141", "LowerLowerBody");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.142", "Tail");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.015", "LeftLeg");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.019", "RightLeg");

	// Rathalos
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone114", "RightLeg");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone98", "LeftLeg");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone115", "RightFoot");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone99", "LeftFoot");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone16", "Head1");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone5", "Head2");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone2", "Body");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone21", "LeftWing");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone60", "RightWing");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone131", "TailWithBody");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone132", "TailConnection");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone133", "Tail");

	// Anjanath
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.031", "Head1");	// Head
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.003", "Head2");	// Neck
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.001", "Body");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.014", "LeftBackLeg");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.018", "RightBackLeg");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.012", "LeftFrontLeg");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.008", "RightFrontLeg");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.080", "LeftBackFoot");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.020", "RightBackFoot");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.141", "TailWithBody");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.143", "Tail");
}