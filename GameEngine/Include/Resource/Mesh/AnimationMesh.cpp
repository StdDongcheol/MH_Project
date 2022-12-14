
#include "AnimationMesh.h"
#include "FBXLoader.h"
#include "../Animation/Skeleton.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"
#include "../Shader/StructuredBuffer.h"
#include "../../Device.h"

CAnimationMesh::CAnimationMesh() :
	m_InstancingCount(100)
{
	SetTypeID<CAnimationMesh>();
	m_MeshType = Mesh_Type::Animation;
}

CAnimationMesh::~CAnimationMesh()
{
	SAFE_DELETE(m_BoneBuffer);
}

int CAnimationMesh::GetBoneCount() const
{
	return (int)m_Skeleton->GetBoneCount();
}

void CAnimationMesh::SetBoneShader()
{
	m_BoneBuffer->SetShader(106, (int)Buffer_Shader_Type::Vertex);
}

void CAnimationMesh::ResetBoneShader()
{
	m_BoneBuffer->ResetShader(106, (int)Buffer_Shader_Type::Vertex);
}

void CAnimationMesh::RenderSetBuffer(int SlotNumber)
{
	unsigned int	Stride = (unsigned int)m_vecMeshSlot[SlotNumber]->VB->Size;
	unsigned int	Offset = 0;

	CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_vecMeshSlot[SlotNumber]->Primitive);
	CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1,
		&m_vecMeshSlot[SlotNumber]->VB->Buffer, &Stride, &Offset);

	if (m_vecMeshSlot[SlotNumber]->IB)
	{
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(
			m_vecMeshSlot[SlotNumber]->IB->Buffer,
			m_vecMeshSlot[SlotNumber]->IB->Fmt, 0);
		CDevice::GetInst()->GetContext()->DrawIndexed(
			m_vecMeshSlot[SlotNumber]->IB->Count, 0, 0);
	}

	else
	{
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(
			nullptr, DXGI_FORMAT_UNKNOWN, 0);
		CDevice::GetInst()->GetContext()->Draw(
			m_vecMeshSlot[SlotNumber]->VB->Count, 0);
	}
}

// fbx
bool CAnimationMesh::Init()
{
	return true;
}

void CAnimationMesh::SetSkeleton(CSkeleton* Skeleton)
{
	m_Skeleton = Skeleton;

	m_BoneBuffer = new CStructuredBuffer;

	m_BoneBuffer->Init("OutputBone", sizeof(Matrix),
		(unsigned int)m_Skeleton->GetBoneCount() * m_InstancingCount, 2);
}

void CAnimationMesh::SetSkeleton(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	m_Skeleton = new CSkeleton;

	char	FileNameMultibyte[MAX_PATH] = {};

	int Length = WideCharToMultiByte(CP_ACP, 0, FileName, -1, 0, 0, 0, 0);
	WideCharToMultiByte(CP_ACP, 0, FileName, -1, FileNameMultibyte, Length, 0, 0);

	m_Skeleton->LoadSkeleton(m_Scene, Name, FileNameMultibyte, PathName);


	m_BoneBuffer = new CStructuredBuffer;

	m_BoneBuffer->Init("OutputBone", sizeof(Matrix),
		(unsigned int)m_Skeleton->GetBoneCount() * m_InstancingCount, 2);
}

bool CAnimationMesh::LoadMeshFullPathMultibyte(const char* FullPath)
{
	char    Ext[_MAX_EXT] = {};

	_splitpath_s(FullPath, 0, 0, 0, 0, 0, 0, Ext, _MAX_EXT);
	_strupr_s(Ext);

	if (strcmp(Ext, ".FBX") == 0)
	{
		CFBXLoader  Loader;

		if (!Loader.LoadFBX(FullPath, false))
			return false;

		return ConvertFBX(&Loader, FullPath);
	}

	return LoadMeshFile(FullPath);
}

bool CAnimationMesh::ConvertFBX(CFBXLoader* Loader, const char* FullPath)
{
	if (!CMesh::ConvertFBX(Loader, FullPath))
		return false;

	// ?????????? ????
	const std::vector<PFBXBONE>* pvecBone = Loader->GetBones();

	if (pvecBone->empty())
		return true;

	std::string	strSkeletonName = m_Name + "_Skeleton";

	m_Skeleton = new CSkeleton;

	// ?? ?????? ????????.
	std::vector<PFBXBONE>::const_iterator	iterB;
	std::vector<PFBXBONE>::const_iterator	iterBEnd = pvecBone->end();

	for (iterB = pvecBone->begin(); iterB != iterBEnd; ++iterB)
	{
		Bone* pBone = new Bone;

		pBone->strName = (*iterB)->strName;
		pBone->iDepth = (*iterB)->iDepth;
		pBone->iParentIndex = (*iterB)->iParentIndex;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				pBone->matOffset[i][j] = (float)(*iterB)->matOffset.mData[i].mData[j];
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				pBone->matBone[i][j] = (float)(*iterB)->matBone.mData[i].mData[j];
			}
		}

		m_Skeleton->AddBone(pBone);
	}

	// ?????????? ?????? ????????.
	const std::vector<PFBXANIMATIONCLIP>* pvecClip = Loader->GetClips();

	// ???? ?????? ?????? ?????? ??????????.
	char	strAnimPath[MAX_PATH] = {};
	strcpy_s(strAnimPath, FullPath);

	int	iLength = (int)strlen(strAnimPath);
	for (int i = iLength - 1; i >= 0; --i)
	{
		// aa/bb.exe 9??, 2???????? 3 ~ 8?????? ????
		if (strAnimPath[i] == '/' || strAnimPath[i] == '\\')
		{
			memset(&strAnimPath[i + 1], 0, sizeof(TCHAR) * (iLength - (i + 1)));
			break;
		}
	}

	// ?????? ????????.
	std::vector<PFBXANIMATIONCLIP>::const_iterator	iterC;
	std::vector<PFBXANIMATIONCLIP>::const_iterator	iterCEnd = pvecClip->end();

	for (iterC = pvecClip->begin(); iterC != iterCEnd; ++iterC)
	{
		m_Scene->GetResource()->LoadAnimationSequence((*iterC)->strName, false, *iterC);

		CAnimationSequence* pSequence = m_Scene->GetResource()->FindAnimationSequence((*iterC)->strName);

		if (!pSequence)
			continue;

		char	strAnimFullPath[MAX_PATH] = {};
		strcpy_s(strAnimFullPath, FullPath);
		memcpy(&strAnimFullPath[iLength - 3], "sqc", 3);

		pSequence->SaveFullPathMultibyte(strAnimFullPath);
	}

	if (m_Skeleton)
	{
		char	SkeletonPath[MAX_PATH] = {};
		strcpy_s(SkeletonPath, FullPath);
		memcpy(&SkeletonPath[iLength - 3], "bne", 3);
		m_Skeleton->SaveSkeletonFullPath(SkeletonPath);


		m_BoneBuffer = new CStructuredBuffer;

		m_BoneBuffer->Init("OutputBone", sizeof(Matrix),
			(unsigned int)m_Skeleton->GetBoneCount() * m_InstancingCount, 2);
	}

	return true;
}

bool CAnimationMesh::SaveMesh(FILE* File)
{
	if (!CMesh::SaveMesh(File))
		return false;

	return true;
}

bool CAnimationMesh::LoadMesh(FILE* File)
{
	if (!CMesh::LoadMesh(File))
		return false;

	return true;
}
