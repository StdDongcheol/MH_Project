
#include "LandScape.h"
#include "../Device.h"
#include "../Input.h"
#include "../PathManager.h"
#include "../Resource/Mesh/StaticMesh.h"
#include "../Scene/Scene.h"
#include "../Scene/Navigation3DManager.h"
#include "../Scene/SceneResource.h"
#include "../Resource/Material/Material.h"
#include "../Resource/Shader/LandScapeConstantBuffer.h"
#include "../Resource/Shader/PickingConstantBuffer.h"
#include "../Resource/Shader/PickingComputeShader.h"
#include "../Resource/Shader/StructuredBuffer.h"
#include "../Scene/Navigation3D.h"
#include "../Scene/NavigationMesh.h"
#include "../Scene/SceneManager.h"

CLandScape::CLandScape() :
	m_CountX(0),
	m_CountZ(0),
	m_SelectMap(-1),
	m_BrushHeight(10.f),
	m_BrushSpaltting(10.f),
	m_Buffer(nullptr),
	m_CBuffer(nullptr),
	m_PickingCBuffer(nullptr),
	m_PickingCS(nullptr),
	m_InputSBuffer(nullptr),
	m_OutputSBuffer(nullptr),
	m_Min(FLT_MAX, FLT_MAX, FLT_MAX),
	m_Max(FLT_MIN, FLT_MIN, FLT_MIN),
	m_VertexSize(0),
	m_InputDesc(nullptr),
	m_OutputDesc(nullptr)
{
	SetTypeID<CLandScape>();
	m_Render = true;
}

CLandScape::CLandScape(const CLandScape& com) :
	CSceneComponent(com)
{
	m_CountX = com.m_CountX;
	m_CountZ = com.m_CountZ;
	m_Mesh = com.m_Mesh;
	m_vecVtx = com.m_vecVtx;
	m_vecPos = com.m_vecPos;
	m_vecIndex = com.m_vecIndex;

	m_CBuffer = com.m_CBuffer->Clone();
	m_PickingCBuffer = com.m_PickingCBuffer->Clone();
	m_PickingCS = com.m_PickingCS->Clone();
	m_InputSBuffer = com.m_InputSBuffer->Clone();
	m_OutputSBuffer = com.m_OutputSBuffer->Clone();

	m_VertexSize = 0;

	m_InputDesc = nullptr;
	m_OutputDesc = nullptr;
}

CLandScape::~CLandScape()
{
	SAFE_RELEASE(m_Buffer);
	SAFE_DELETE_ARRAY(m_OutputDesc);
	SAFE_DELETE_ARRAY(m_InputDesc);
	SAFE_DELETE(m_InputSBuffer);
	SAFE_DELETE(m_OutputSBuffer);
	SAFE_DELETE(m_PickingCBuffer);
	SAFE_DELETE(m_CBuffer);
}

void CLandScape::CreateLandScape(const std::string& Name, int CountX, int CountZ, const TCHAR* HeightMap, const std::string& PathName)
{
	m_CountX = CountX;
	m_CountZ = CountZ;

	std::vector<float>	vecY;

	if (HeightMap)
	{
		TCHAR	FullPath[MAX_PATH] = {};

		const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

		if (Path)
			lstrcpy(FullPath, Path->Path);
		lstrcat(FullPath, HeightMap);

		ScratchImage	Img;

		char	Ext[_MAX_EXT] = {};
		char	FullPathMultibyte[MAX_PATH] = {};

#ifdef UNICODE

		int	ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
		WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else

		strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

		_splitpath_s(FullPathMultibyte, nullptr, 0, nullptr, 0, nullptr, 0, Ext, _MAX_EXT);

		_strupr_s(Ext);

		if (strcmp(Ext, ".DDS") == 0)
		{
			if (FAILED(LoadFromDDSFile(FullPath, DDS_FLAGS_NONE, nullptr, Img)))
			{
				return;
			}
		}

		else if (strcmp(Ext, ".TGA") == 0)
		{
			if (FAILED(LoadFromTGAFile(FullPath, nullptr, Img)))
			{
				return;
			}
		}

		else
		{
			if (FAILED(LoadFromWICFile(FullPath, WIC_FLAGS_NONE, nullptr, Img)))
			{
				return;
			}
		}

		// 픽셀 값을 꺼내온다.
		const Image* PixelInfo = Img.GetImages();

		for (size_t i = 0; i < PixelInfo->height; ++i)
		{
			for (size_t j = 0; j < PixelInfo->width; ++j)
			{
				int	PixelIndex = (int)i * (int)PixelInfo->width * 4 + (int)j * 4;

				float	Y = PixelInfo->pixels[PixelIndex] / 30.f;

				vecY.push_back(Y);
			}
		}
	}

	else
		vecY.resize(CountX * CountZ);

	for (int i = 0; i < m_CountZ; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			Vertex3DSplatting	Vtx = {};

			Vtx.Pos = Vector3((float)j, vecY[i * m_CountX + j], (float)m_CountZ - i - 1);

			if (m_CountX != 100 && m_CountZ != 100)
				Vtx.UV = Vector2((j / (float)(m_CountX - 1)) * 100.f, (i / (float)m_CountZ - 1) * 100.f);

			m_vecPos.push_back(Vtx.Pos);


			if (m_Min.x > Vtx.Pos.x)
				m_Min.x = Vtx.Pos.x;

			if (m_Min.y > Vtx.Pos.y)
				m_Min.y = Vtx.Pos.y;

			if (m_Min.z > Vtx.Pos.z)
				m_Min.z = Vtx.Pos.z;

			if (m_Max.x < Vtx.Pos.x)
				m_Max.x = Vtx.Pos.x;

			if (m_Max.y < Vtx.Pos.y)
				m_Max.y = Vtx.Pos.y;

			if (m_Max.z < Vtx.Pos.z)
				m_Max.z = Vtx.Pos.z;

			m_vecVtx.push_back(Vtx);
		}
	}

	SetMeshSize(m_Max - m_Min);
	m_SphereInfo.Center = (m_Max + m_Min) / 2.f;

	// 인덱스 정보 만들기
	// 면 법선은 삼각형 수만큼 만들어져야 한다.
	Vector3	TrianglePos[3];
	Vector3	Edge1, Edge2;
	unsigned int	TriIndex = 0;

	m_vecFaceNormal.resize((m_CountX - 1) * (m_CountZ - 1) * 2);

	for (unsigned int i = 0; i < (unsigned int)m_CountZ - 1; ++i)
	{
		for (unsigned int j = 0; j < (unsigned int)m_CountX - 1; ++j)
		{
			unsigned int	Index = i * m_CountX + j;

			// 사각형의 우 상단 삼각형
			m_vecIndex.push_back(Index);
			m_vecIndex.push_back(Index + 1);
			m_vecIndex.push_back(Index + m_CountX + 1);

			TrianglePos[0] = m_vecVtx[Index].Pos;
			TrianglePos[1] = m_vecVtx[Index + 1].Pos;
			TrianglePos[2] = m_vecVtx[Index + m_CountX + 1].Pos;

			Edge1 = TrianglePos[1] - TrianglePos[0];
			Edge2 = TrianglePos[2] - TrianglePos[0];

			Edge1.Normalize();
			Edge2.Normalize();

			m_vecFaceNormal[TriIndex] = Edge1.Cross(Edge2);
			m_vecFaceNormal[TriIndex].Normalize();

			++TriIndex;


			// 사각형의 좌 하단 삼각형
			m_vecIndex.push_back(Index);
			m_vecIndex.push_back(Index + m_CountX + 1);
			m_vecIndex.push_back(Index + m_CountX);

			TrianglePos[0] = m_vecVtx[Index].Pos;
			TrianglePos[1] = m_vecVtx[Index + m_CountX + 1].Pos;
			TrianglePos[2] = m_vecVtx[Index + m_CountX].Pos;

			Edge1 = TrianglePos[1] - TrianglePos[0];
			Edge2 = TrianglePos[2] - TrianglePos[0];

			Edge1.Normalize();
			Edge2.Normalize();

			m_vecFaceNormal[TriIndex] = Edge1.Cross(Edge2);
			m_vecFaceNormal[TriIndex].Normalize();

			++TriIndex;
		}
	}

	ComputeNormal();

	ComputeTangent();

	// 메쉬를 만든다.
	m_Scene->GetResource()->CreateMesh(Mesh_Type::Static, Name, &m_vecVtx[0], sizeof(Vertex3DSplatting), (int)m_vecVtx.size(), D3D11_USAGE_DEFAULT, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, &m_vecIndex[0], sizeof(int), (int)m_vecIndex.size(),
		D3D11_USAGE_DEFAULT, DXGI_FORMAT_R32_UINT);

	m_Mesh = (CStaticMesh*)m_Scene->GetResource()->FindMesh(Name);


	m_VertexSize = (unsigned int)m_vecIndex.size() / 3;

	m_InputDesc = DBG_NEW PickingInputDesc[m_VertexSize];

	for (unsigned int i = 0; i < m_VertexSize; ++i)
	{
		unsigned int index0 = m_vecIndex[i * 3];
		unsigned int index1 = m_vecIndex[i * 3 + 1];
		unsigned int index2 = m_vecIndex[i * 3 + 2];

		m_InputDesc[i].V0 = m_vecVtx[index0].Pos;
		m_InputDesc[i].V1 = m_vecVtx[index1].Pos;
		m_InputDesc[i].V2 = m_vecVtx[index2].Pos;

		m_InputDesc[i].Index = i;
	}

	m_Scene->GetNavigation3DManager()->AddNavData(this);

	m_OutputDesc = DBG_NEW PickingOutputDesc[m_VertexSize];
	memset(m_OutputDesc, 0, sizeof(PickingOutputDesc) * m_VertexSize);

	if (m_Scene)
		m_PickingCS = (CPickingComputeShader*)m_Scene->GetResource()->FindShader("PickingComputeShader");

	else
		m_PickingCS = (CPickingComputeShader*)CResourceManager::GetInst()->FindShader("PickingComputeShader");

	m_InputSBuffer = DBG_NEW CStructuredBuffer;

	m_InputSBuffer->Init("PickingInputBuffer", sizeof(PickingInputDesc), (unsigned int)m_VertexSize, 25, true, (int)Buffer_Shader_Type::Compute);

	m_InputSBuffer->UpdateBuffer(&m_InputDesc[0], (unsigned)m_VertexSize);

	m_OutputSBuffer = DBG_NEW CStructuredBuffer;
	m_OutputSBuffer->Init("PickingOutputBuffer", sizeof(PickingOutputDesc), (unsigned int)m_VertexSize, 5);

	D3D11_BUFFER_DESC	Desc = {};

	Desc.ByteWidth = sizeof(PickingOutputDesc) * (unsigned int)m_VertexSize;
	Desc.Usage = D3D11_USAGE_STAGING;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_Buffer);
}

void CLandScape::SetMaterial(CMaterial* Material, int Index)
{
	m_vecMaterialSlot[Index] = Material->Clone();

	m_vecMaterialSlot[Index]->SetScene(m_Scene);
}

void CLandScape::SetMaterial(const std::string& Name, int Index)
{
	CMaterial* Material = m_Scene->GetResource()->FindMaterial(Name);

	m_vecMaterialSlot[Index] = Material->Clone();

	m_vecMaterialSlot[Index]->SetScene(m_Scene);
}

void CLandScape::AddMaterial(CMaterial* Material)
{
	m_vecMaterialSlot.push_back(Material->Clone());

	m_vecMaterialSlot[m_vecMaterialSlot.size() - 1]->SetScene(m_Scene);
}

void CLandScape::AddMaterial(const std::string& Name)
{
	CMaterial* Material = m_Scene->GetResource()->FindMaterial(Name);

	m_vecMaterialSlot.push_back(Material->Clone());

	m_vecMaterialSlot[m_vecMaterialSlot.size() - 1]->SetScene(m_Scene);
}

void CLandScape::SetDetailLevel(float Level)
{
	m_CBuffer->SetDetailLevel(Level);
}

void CLandScape::SetSplatCount(int Count)
{
	m_CBuffer->SetSplatCount(Count);
}

void CLandScape::CreateNavigationData(CNavigationMesh* NavMesh)
{
	float	CellSizeX = 0.f, CellSizeZ = 0.f;

	CellSizeX = m_vecVtx[1].Pos.x - m_vecVtx[0].Pos.x;
	CellSizeZ = m_vecVtx[0].Pos.z - m_vecVtx[m_CountX].Pos.z;

	Vector3	CellPos[3];

	for (int i = 0; i < m_CountZ - 1; ++i)
	{
		for (int j = 0; j < m_CountX - 1; ++j)
		{
			UINT	Index = i * m_CountX + j;

			CellPos[0] = m_vecVtx[Index].Pos;
			CellPos[1] = m_vecVtx[Index + 1].Pos;
			CellPos[2] = m_vecVtx[Index + m_CountX + 1].Pos;

			int CellTextureType[3];

			CellTextureType[0] = m_vecVtx[Index].SPLTextureType;
			CellTextureType[1] = m_vecVtx[Index + 1].SPLTextureType;
			CellTextureType[2] = m_vecVtx[Index + m_CountX + 1].SPLTextureType;

			NavMesh->AddCell(CellPos, CellTextureType);

			// 좌하단 삼각형
			CellPos[0] = m_vecVtx[Index].Pos;
			CellPos[1] = m_vecVtx[Index + m_CountX + 1].Pos;
			CellPos[2] = m_vecVtx[Index + m_CountX].Pos;

			CellTextureType[0] = m_vecVtx[Index].SPLTextureType;
			CellTextureType[1] = m_vecVtx[Index + m_CountX + 1].SPLTextureType;
			CellTextureType[2] = m_vecVtx[Index + m_CountX].SPLTextureType;

			NavMesh->AddCell(CellPos, CellTextureType);
		}
	}

	NavMesh->SetCellSize(CellSizeX, CellSizeZ);

	NavMesh->CreateGridMapAdj(m_CountX - 1);
}

void CLandScape::ReleaseMesh()
{
	std::string	MeshName = m_Mesh->GetName();

	m_Mesh = nullptr;

	m_Scene->GetResource()->ReleaseMesh(MeshName);
}

void CLandScape::PlayBrush(float DeltaTime, bool Up)
{
	switch (GetBrushType())
	{
	case 1: // 원 브러쉬
	{
		int Size = (int)m_vecVtx.size();

		for (int i = 0; i < Size; ++i)
		{
			Vector3 p1 = Vector3(m_vecVtx[i].Pos.x, 0.f, m_vecVtx[i].Pos.z);
			Vector3 p2 = Vector3(m_DDTPos.x, 0.f, m_DDTPos.z);

			float dist = (p2 - p1).Length();
			float cosV = cos(XM_PIDIV2 * dist / GetBrushRange()); // XM_PIDIV2 : PI / 2
			float value = m_BrushHeight * max(0.f, cosV) * DeltaTime;

			if (dist <= GetBrushRange())
			{
				if (Up)
				{
					m_vecVtx[i].Pos.y += value;
					m_vecPos[i].y += value;
				}

				else
				{
					m_vecVtx[i].Pos.y -= value;
					m_vecPos[i].y -= value;
				}
			}
		}
	}
		break;
	case 2: // 사각형 브러쉬
	{
		int Size = (int)m_vecVtx.size();

		for (int i = 0; i < Size; ++i)
		{
			Vector3 p1 = Vector3(m_vecVtx[i].Pos.x, 0.f, m_vecVtx[i].Pos.z);
			Vector3 p2 = Vector3(m_DDTPos.x, 0.f, m_DDTPos.z);

			float distX = abs(p2.x - p1.x);
			float distZ = abs(p2.z - p1.z);
			float value = m_BrushHeight * DeltaTime;

			if (distX <= GetBrushRange() && distZ <= GetBrushRange())
			{
				if (Up)
				{
					m_vecVtx[i].Pos.y += value;
					m_vecPos[i].y += value;
				}

				else
				{
					m_vecVtx[i].Pos.y -= value;
					m_vecPos[i].y -= value;
				}
			}
		}
	}
		break;
	}

	m_Mesh->UpdateVertex(&m_vecVtx[0], (UINT)m_vecVtx.size());
}

void CLandScape::PlaySplatting(float DeltaTime, bool Draw, int TextureType)
{
	if (m_SelectMap == -1)
		return;

	switch (GetBrushType())
	{
	case 1: // 원 브러쉬
	{
		int Size = (int)m_vecVtx.size();

		for (int i = 0; i < Size; ++i)
		{
			Vector3 p1 = Vector3(m_vecVtx[i].Pos.x, 0.f, m_vecVtx[i].Pos.z);
			Vector3 p2 = Vector3(m_DDTPos.x, 0.f, m_DDTPos.z);

			float dist = (p2 - p1).Length();
			float cosV = cos(XM_PIDIV2 * dist / GetBrushRange()); // XM_PIDIV2 : PI / 2
			float value = m_BrushSpaltting * max(0.f, cosV) * DeltaTime;

			if (dist <= GetBrushRange())
			{
				if (Draw)
				{
					/*
					0	1	2	3	->	SPLTexture,  SPLNormal
					4	5	6	7	->	SPLTexture2, SPLNormal2
					8	9	10	11	->	SPLTexture3, SPLNormal3
					*/
					for (int j = 0; j < 4; ++j)
					{
						if (m_SelectMap >= 8)
						{
							if (m_SelectMap - 8 == j)
							{
								m_vecVtx[i].SPLTextureType = TextureType;

								m_vecVtx[i].SPLTexture3[j] += value;
								m_vecVtx[i].SPLNormal3[j] += value;

								m_vecVtx[i].SPLTexture[j] -= value;
								m_vecVtx[i].SPLTexture2[j] -= value;
								m_vecVtx[i].SPLNormal[j] -= value;
								m_vecVtx[i].SPLNormal2[j] -= value;
							}

							else
							{
								m_vecVtx[i].SPLTexture[j] -= value;
								m_vecVtx[i].SPLTexture2[j] -= value;
								m_vecVtx[i].SPLTexture3[j] -= value;
								m_vecVtx[i].SPLNormal[j] -= value;
								m_vecVtx[i].SPLNormal2[j] -= value;
								m_vecVtx[i].SPLNormal3[j] -= value;
							}
						}

						else if (m_SelectMap >= 4)
						{
							if (m_SelectMap - 4 == j)
							{
								m_vecVtx[i].SPLTextureType = TextureType;

								m_vecVtx[i].SPLTexture2[j] += value;
								m_vecVtx[i].SPLNormal2[j] += value;

								m_vecVtx[i].SPLTexture[j] -= value;
								m_vecVtx[i].SPLTexture3[j] -= value;
								m_vecVtx[i].SPLNormal[j] -= value;
								m_vecVtx[i].SPLNormal3[j] -= value;
							}

							else
							{
								m_vecVtx[i].SPLTexture[j] -= value;
								m_vecVtx[i].SPLTexture2[j] -= value;
								m_vecVtx[i].SPLTexture3[j] -= value;
								m_vecVtx[i].SPLNormal[j] -= value;
								m_vecVtx[i].SPLNormal2[j] -= value;
								m_vecVtx[i].SPLNormal3[j] -= value;
							}
						}

						else
						{
							if (m_SelectMap == j)
							{
								m_vecVtx[i].SPLTextureType = TextureType;

								m_vecVtx[i].SPLTexture[j] += value;
								m_vecVtx[i].SPLNormal[j] += value;

								m_vecVtx[i].SPLTexture2[j] -= value;
								m_vecVtx[i].SPLTexture3[j] -= value;
								m_vecVtx[i].SPLNormal2[j] -= value;
								m_vecVtx[i].SPLNormal3[j] -= value;
							}

							else
							{
								m_vecVtx[i].SPLTexture[j] -= value;
								m_vecVtx[i].SPLTexture2[j] -= value;
								m_vecVtx[i].SPLTexture3[j] -= value;
								m_vecVtx[i].SPLNormal[j] -= value;
								m_vecVtx[i].SPLNormal2[j] -= value;
								m_vecVtx[i].SPLNormal3[j] -= value;
							}
						}
					}
				}

				else
				{
					for (int j = 0; j < 4; ++j)
					{
						m_vecVtx[i].SPLTextureType = TextureType;// == 0 ? 1 : 0;

						m_vecVtx[i].SPLTexture[j] -= value;
						m_vecVtx[i].SPLTexture2[j] -= value;
						m_vecVtx[i].SPLTexture3[j] -= value;
						m_vecVtx[i].SPLNormal[j] -= value;
						m_vecVtx[i].SPLNormal2[j] -= value;
						m_vecVtx[i].SPLNormal3[j] -= value;
					}
				}

				for (int j = 0; j < 4; ++j)
				{
					m_vecVtx[i].SPLTexture[j] = max(0.f, min(1.f, m_vecVtx[i].SPLTexture[j]));
					m_vecVtx[i].SPLTexture2[j] = max(0.f, min(1.f, m_vecVtx[i].SPLTexture2[j]));
					m_vecVtx[i].SPLTexture3[j] = max(0.f, min(1.f, m_vecVtx[i].SPLTexture3[j]));
					m_vecVtx[i].SPLNormal[j] = max(0.f, min(1.f, m_vecVtx[i].SPLNormal[j]));
					m_vecVtx[i].SPLNormal2[j] = max(0.f, min(1.f, m_vecVtx[i].SPLNormal2[j]));
					m_vecVtx[i].SPLNormal3[j] = max(0.f, min(1.f, m_vecVtx[i].SPLNormal3[j]));
				}
			}
		}
	}
	break;
	case 2: // 사각형 브러쉬
	{
		int Size = (int)m_vecVtx.size();

		for (int i = 0; i < Size; ++i)
		{
			Vector3 p1 = Vector3(m_vecVtx[i].Pos.x, 0.f, m_vecVtx[i].Pos.z);
			Vector3 p2 = Vector3(m_DDTPos.x, 0.f, m_DDTPos.z);

			float distX = abs(p2.x - p1.x);
			float distZ = abs(p2.z - p1.z);

			float value = m_BrushSpaltting * DeltaTime;

			if (distX <= GetBrushRange() && distZ <= GetBrushRange())
			{
				if (Draw)
				{
					/*
					0	1	2	3	->	SPLTexture,  SPLNormal
					4	5	6	7	->	SPLTexture2, SPLNormal2
					8	9	10	11	->	SPLTexture3, SPLNormal3
					*/
					for (int j = 0; j < 4; ++j)
					{
						if (m_SelectMap >= 8)
						{
							if (m_SelectMap - 8 == j)
							{
								m_vecVtx[i].SPLTextureType = TextureType;

								m_vecVtx[i].SPLTexture3[j] += value;
								m_vecVtx[i].SPLNormal3[j] += value;

								m_vecVtx[i].SPLTexture[j] -= value;
								m_vecVtx[i].SPLTexture2[j] -= value;
								m_vecVtx[i].SPLNormal[j] -= value;
								m_vecVtx[i].SPLNormal2[j] -= value;
							}

							else
							{
								m_vecVtx[i].SPLTexture[j] -= value;
								m_vecVtx[i].SPLTexture2[j] -= value;
								m_vecVtx[i].SPLTexture3[j] -= value;
								m_vecVtx[i].SPLNormal[j] -= value;
								m_vecVtx[i].SPLNormal2[j] -= value;
								m_vecVtx[i].SPLNormal3[j] -= value;
							}
						}

						else if (m_SelectMap >= 4)
						{
							if (m_SelectMap - 4 == j)
							{
								m_vecVtx[i].SPLTextureType = TextureType;

								m_vecVtx[i].SPLTexture2[j] += value;
								m_vecVtx[i].SPLNormal2[j] += value;

								m_vecVtx[i].SPLTexture[j] -= value;
								m_vecVtx[i].SPLTexture3[j] -= value;
								m_vecVtx[i].SPLNormal[j] -= value;
								m_vecVtx[i].SPLNormal3[j] -= value;
							}

							else
							{
								m_vecVtx[i].SPLTexture[j] -= value;
								m_vecVtx[i].SPLTexture2[j] -= value;
								m_vecVtx[i].SPLTexture3[j] -= value;
								m_vecVtx[i].SPLNormal[j] -= value;
								m_vecVtx[i].SPLNormal2[j] -= value;
								m_vecVtx[i].SPLNormal3[j] -= value;
							}
						}

						else
						{
							if (m_SelectMap == j)
							{
								m_vecVtx[i].SPLTextureType = TextureType;

								m_vecVtx[i].SPLTexture[j] += value;
								m_vecVtx[i].SPLNormal[j] += value;

								m_vecVtx[i].SPLTexture2[j] -= value;
								m_vecVtx[i].SPLTexture3[j] -= value;
								m_vecVtx[i].SPLNormal2[j] -= value;
								m_vecVtx[i].SPLNormal3[j] -= value;
							}

							else
							{
								m_vecVtx[i].SPLTexture[j] -= value;
								m_vecVtx[i].SPLTexture2[j] -= value;
								m_vecVtx[i].SPLTexture3[j] -= value;
								m_vecVtx[i].SPLNormal[j] -= value;
								m_vecVtx[i].SPLNormal2[j] -= value;
								m_vecVtx[i].SPLNormal3[j] -= value;
							}
						}
					}
				}

				else
				{
					for (int j = 0; j < 4; ++j)
					{
						m_vecVtx[i].SPLTextureType = TextureType == 0 ? 1 : 0;

						m_vecVtx[i].SPLTexture[j] -= value;
						m_vecVtx[i].SPLTexture2[j] -= value;
						m_vecVtx[i].SPLTexture3[j] -= value;
						m_vecVtx[i].SPLNormal[j] -= value;
						m_vecVtx[i].SPLNormal2[j] -= value;
						m_vecVtx[i].SPLNormal3[j] -= value;
					}
				}

				for (int j = 0; j < 4; ++j)
				{
					m_vecVtx[i].SPLTexture[j] = max(0.f, min(1.f, m_vecVtx[i].SPLTexture[j]));
					m_vecVtx[i].SPLTexture2[j] = max(0.f, min(1.f, m_vecVtx[i].SPLTexture2[j]));
					m_vecVtx[i].SPLTexture3[j] = max(0.f, min(1.f, m_vecVtx[i].SPLTexture3[j]));
					m_vecVtx[i].SPLNormal[j] = max(0.f, min(1.f, m_vecVtx[i].SPLNormal[j]));
					m_vecVtx[i].SPLNormal2[j] = max(0.f, min(1.f, m_vecVtx[i].SPLNormal2[j]));
					m_vecVtx[i].SPLNormal3[j] = max(0.f, min(1.f, m_vecVtx[i].SPLNormal3[j]));
				}
			}
		}
	}
	break;
	}

	m_Mesh->UpdateVertex(&m_vecVtx[0], (UINT)m_vecVtx.size());
}

int CLandScape::GetBrushType() const
{
	return m_CBuffer->GetBrushType();
}

Vector3 CLandScape::GetBrushLocation() const
{
	return m_CBuffer->GetBrushLocation();
}

float CLandScape::GetBrushRange() const
{
	return m_CBuffer->GetBrushRange();
}

Vector3 CLandScape::GetBrushColor() const
{
	return m_CBuffer->GetBrushColor();
}

void CLandScape::SetBrushType(int Type)
{
	m_CBuffer->SetBrushType(Type);
}

void CLandScape::SetBrushType(Brush_Type Type)
{
	m_CBuffer->SetBrushType(Type);
}

void CLandScape::SetBrushLocation(const Vector3& Location)
{
	m_CBuffer->SetBrushLocation(Location);
}

void CLandScape::SetBrushRange(float Range)
{
	m_CBuffer->SetBrushRange(Range);
}

void CLandScape::SetBrushColor(const Vector3& Color)
{
	m_CBuffer->SetBrushColor(Color);
}

float CLandScape::GetHeight(const Vector3& Pos)
{
	Vector3	Convert = (Pos - GetWorldPos()) / GetWorldScale();

	// z 좌표 역으로 계산
	Convert.z = m_CountZ - 1 - Convert.z;

	int	IndexX = (int)Convert.x;
	int	IndexZ = (int)Convert.z;

	if (IndexX < 0 || IndexX >= m_CountX || IndexZ < 0 || IndexZ >= m_CountZ - 1)
		return Pos.y;

	int	Index = IndexZ * m_CountX + IndexX;

	float	RatioX = Convert.x - IndexX;
	float	RatioZ = Convert.z - IndexZ;

	float	Y[4] =
	{
		m_vecPos[Index].y,
		m_vecPos[Index + 1].y,
		m_vecPos[Index + m_CountX].y,
		m_vecPos[Index + m_CountX + 1].y
	};

	// 우상단 삼각형
	if (RatioX > RatioZ)
		return Y[0] + (Y[1] - Y[0]) * RatioX + (Y[3] - Y[1]) * RatioZ;

	return Y[0] + (Y[3] - Y[2]) * RatioX + (Y[2] - Y[0]) * RatioZ;
}

void CLandScape::Start()
{
	CSceneComponent::Start();
}

bool CLandScape::Init()
{
	m_CBuffer = DBG_NEW CLandScapeConstantBuffer;

	m_CBuffer->Init();

	if (CEngine::GetInst()->IsEditMode())
	{
		m_PickingCBuffer = DBG_NEW CPickingConstantBuffer;

		m_PickingCBuffer->Init();

		SetBrushType(Brush_Type::Circle);
		SetBrushRange(10.f);
		SetBrushColor(Vector3::Green);
	}

	return true;
}

void CLandScape::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CLandScape::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CLandScape::PrevRender()
{
	CSceneComponent::PrevRender();
}

void CLandScape::Render()
{
	CSceneComponent::Render();

	if (!m_Mesh)
		return;

	m_CBuffer->UpdateCBuffer();

	size_t	Size = m_vecMaterialSlot.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecMaterialSlot[i]->EnableDecal(m_ReceiveDecal);

		m_vecMaterialSlot[i]->Render();

		m_Mesh->Render((int)i);

		m_vecMaterialSlot[i]->Reset();
	}
}

void CLandScape::RenderShadowMap()
{
	CSceneComponent::RenderShadowMap();
}


void CLandScape::PostRender()
{
	CSceneComponent::PostRender();

	if (CEngine::GetInst()->IsEditMode())
	{
		if (ComputePicking(&m_DDTPos))
			m_CBuffer->SetBrushLocation(m_DDTPos);
	}
}

CLandScape* CLandScape::Clone()
{
	return DBG_NEW CLandScape(*this);
}

void CLandScape::Save(FILE* File)
{
	fwrite(&m_CountX, sizeof(int), 1, File);
	fwrite(&m_CountZ, sizeof(int), 1, File);

	size_t Size = (size_t)(m_CountX * m_CountZ);

	fwrite(&m_vecPos[0], sizeof(Vector3), Size, File);
	fwrite(&m_vecVtx[0], sizeof(Vertex3DSplatting), Size, File);

	fwrite(&m_Max, sizeof(Vector3), 1, File);
	fwrite(&m_Min, sizeof(Vector3), 1, File);

	Size = m_vecIndex.size();
	fwrite(&Size, sizeof(size_t), 1, File);
	fwrite(&m_vecIndex[0], sizeof(unsigned int), Size, File);

	Size = m_vecFaceNormal.size();
	fwrite(&Size, sizeof(size_t), 1, File);
	fwrite(&m_vecFaceNormal[0], sizeof(Vector3), Size, File);

	fwrite(&m_VertexSize, sizeof(unsigned int), 1, File);
	fwrite(&m_InputDesc[0], sizeof(PickingInputDesc), m_VertexSize, File);
	fwrite(&m_OutputDesc[0], sizeof(PickingOutputDesc), m_VertexSize, File);

	m_Scene->GetNavigation3DManager()->Save(File, this);
}

void CLandScape::Load(FILE* File)
{
	SAFE_RELEASE(m_Buffer);
	SAFE_DELETE_ARRAY(m_OutputDesc);
	SAFE_DELETE_ARRAY(m_InputDesc);
	SAFE_DELETE(m_InputSBuffer);
	SAFE_DELETE(m_OutputSBuffer);

	fread(&m_CountX, sizeof(int), 1, File);
	fread(&m_CountZ, sizeof(int), 1, File);

	size_t Size = (size_t)(m_CountX * m_CountZ);
	m_vecPos.clear();
	m_vecVtx.clear();

	m_vecPos.resize(Size);
	m_vecVtx.resize(Size);	

	fread(&m_vecPos[0], sizeof(Vector3), Size, File);
	fread(&m_vecVtx[0], sizeof(Vertex3DSplatting), Size, File);

	fread(&m_Max, sizeof(Vector3), 1, File);
	fread(&m_Min, sizeof(Vector3), 1, File);

	SetMeshSize(m_Max - m_Min);
	m_SphereInfo.Center = (m_Max + m_Min) / 2.f;

	fread(&Size, sizeof(size_t), 1, File);

	m_vecIndex.clear();
	m_vecIndex.resize(Size);

	fread(&m_vecIndex[0], sizeof(unsigned int), Size, File);

	fread(&Size, sizeof(size_t), 1, File);

	m_vecFaceNormal.clear();
	m_vecFaceNormal.resize(Size);

	fread(&m_vecFaceNormal[0], sizeof(Vector3), Size, File);

	// 메쉬를 만든다.
	m_Scene->GetResource()->CreateMesh(Mesh_Type::Static, "LandScape", &m_vecVtx[0], sizeof(Vertex3DSplatting), (int)m_vecVtx.size(), D3D11_USAGE_DEFAULT, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, &m_vecIndex[0], sizeof(int), (int)m_vecIndex.size(),
		D3D11_USAGE_DEFAULT, DXGI_FORMAT_R32_UINT);

	m_Mesh = (CStaticMesh*)m_Scene->GetResource()->FindMesh("LandScape");

	fread(&m_VertexSize, sizeof(unsigned int), 1, File);

	m_InputDesc = DBG_NEW PickingInputDesc[m_VertexSize];
	fread(&m_InputDesc[0], sizeof(PickingInputDesc), m_VertexSize, File);

	m_OutputDesc = DBG_NEW PickingOutputDesc[m_VertexSize];
	fread(&m_OutputDesc[0], sizeof(PickingOutputDesc), m_VertexSize, File);

	if (m_Scene)
		m_PickingCS = (CPickingComputeShader*)m_Scene->GetResource()->FindShader("PickingComputeShader");

	else
		m_PickingCS = (CPickingComputeShader*)CResourceManager::GetInst()->FindShader("PickingComputeShader");

	m_InputSBuffer = DBG_NEW CStructuredBuffer;
	m_InputSBuffer->Init("PickingInputBuffer", sizeof(PickingInputDesc), (unsigned int)m_VertexSize, 25, true, (int)Buffer_Shader_Type::Compute);
	m_InputSBuffer->UpdateBuffer(&m_InputDesc[0], (unsigned)m_VertexSize);

	m_OutputSBuffer = DBG_NEW CStructuredBuffer;
	m_OutputSBuffer->Init("PickingOutputBuffer", sizeof(PickingOutputDesc), (unsigned int)m_VertexSize, 5);

	D3D11_BUFFER_DESC	Desc = {};

	Desc.ByteWidth = sizeof(PickingOutputDesc) * (unsigned int)m_VertexSize;
	Desc.Usage = D3D11_USAGE_STAGING;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_Buffer);

	m_Scene->GetNavigation3DManager()->Load(File, this);
}

void CLandScape::ComputeNormal()
{
	size_t	Size = m_vecFaceNormal.size();

	for (size_t i = 0; i < Size; ++i)
	{
		unsigned int	Idx0 = m_vecIndex[i * 3];
		unsigned int	Idx1 = m_vecIndex[i * 3 + 1];
		unsigned int	Idx2 = m_vecIndex[i * 3 + 2];

		m_vecVtx[Idx0].Normal += m_vecFaceNormal[i];
		m_vecVtx[Idx1].Normal += m_vecFaceNormal[i];
		m_vecVtx[Idx2].Normal += m_vecFaceNormal[i];
	}

	Size = m_vecVtx.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecVtx[i].Normal.Normalize();
	}
}

void CLandScape::ComputeTangent()
{
	// 탄젠트 벡터 구함.
	for (size_t i = 0; i < m_vecFaceNormal.size(); ++i)
	{
		int	idx0 = m_vecIndex[i * 3];
		int	idx1 = m_vecIndex[i * 3 + 1];
		int	idx2 = m_vecIndex[i * 3 + 2];

		float	fVtx1[3], fVtx2[3];
		fVtx1[0] = m_vecVtx[idx1].Pos.x - m_vecVtx[idx0].Pos.x;
		fVtx1[1] = m_vecVtx[idx1].Pos.y - m_vecVtx[idx0].Pos.y;
		fVtx1[2] = m_vecVtx[idx1].Pos.z - m_vecVtx[idx0].Pos.z;

		fVtx2[0] = m_vecVtx[idx2].Pos.x - m_vecVtx[idx0].Pos.x;
		fVtx2[1] = m_vecVtx[idx2].Pos.y - m_vecVtx[idx0].Pos.y;
		fVtx2[2] = m_vecVtx[idx2].Pos.z - m_vecVtx[idx0].Pos.z;

		float	ftu[2], ftv[2];
		ftu[0] = m_vecVtx[idx1].UV.x - m_vecVtx[idx0].UV.x;
		ftv[0] = m_vecVtx[idx1].UV.y - m_vecVtx[idx0].UV.y;

		ftu[1] = m_vecVtx[idx2].UV.x - m_vecVtx[idx0].UV.x;
		ftv[1] = m_vecVtx[idx2].UV.y - m_vecVtx[idx0].UV.y;

		float	fDen = 1.f / (ftu[0] * ftv[1] - ftu[1] * ftv[0]);

		Vector3	Tangent;
		Tangent.x = (ftv[1] * fVtx1[0] - ftv[0] * fVtx2[0]) * fDen;
		Tangent.y = (ftv[1] * fVtx1[1] - ftv[0] * fVtx2[1]) * fDen;
		Tangent.z = (ftv[1] * fVtx1[2] - ftv[0] * fVtx2[2]) * fDen;

		Tangent.Normalize();

		m_vecVtx[idx0].Tangent = Tangent;
		m_vecVtx[idx1].Tangent = Tangent;
		m_vecVtx[idx2].Tangent = Tangent;

		m_vecVtx[idx0].Binormal = m_vecVtx[idx0].Normal.Cross(Tangent);
		m_vecVtx[idx1].Binormal = m_vecVtx[idx1].Normal.Cross(Tangent);
		m_vecVtx[idx2].Binormal = m_vecVtx[idx2].Normal.Cross(Tangent);

		m_vecVtx[idx0].Binormal.Normalize();
		m_vecVtx[idx1].Binormal.Normalize();
		m_vecVtx[idx2].Binormal.Normalize();
	}
}

bool CLandScape::ComputePicking(Vector3* Pos)
{
	Ray Ray = CInput::GetInst()->GetRay(m_Scene->GetCameraManager()->GetCurrentCamera()->GetViewMatrix());

	m_PickingCBuffer->SetRayPos(Ray.Pos);
	m_PickingCBuffer->SetRayDir(Ray.Dir);
	m_PickingCBuffer->SetRayOutputSize(m_VertexSize);

	m_PickingCBuffer->UpdateCBuffer();

	m_InputSBuffer->SetShader();
	m_OutputSBuffer->SetShader();

	unsigned int x = (unsigned int)ceil((float)m_VertexSize / 512.f);

	m_PickingCS->Excute(x, 1, 1);

	m_InputSBuffer->ResetShader();
	m_OutputSBuffer->ResetShader();

	CDevice::GetInst()->GetContext()->CopyResource(m_Buffer, m_OutputSBuffer->GetBuffer());

	D3D11_MAPPED_SUBRESOURCE	Map = {};

	CDevice::GetInst()->GetContext()->Map(m_Buffer, 0, D3D11_MAP_READ, 0, &Map);

	memcpy(&m_OutputDesc[0], Map.pData, sizeof(PickingOutputDesc) * m_VertexSize);

	CDevice::GetInst()->GetContext()->Unmap(m_Buffer, 0);

	float minDist = FLT_MAX;
	int	minIndex = -1;

	PickingOutputDesc	output = {};

	for (unsigned int i = 0; i < m_VertexSize; ++i)
	{
		output = m_OutputDesc[i];

		if (output.Picked)
		{
			if (minDist > output.Dist)
			{
				minDist = output.Dist;
				minIndex = i;
			}
		}
	}

	if (minIndex >= 0)
	{
		*Pos = Ray.Pos + Ray.Dir * minDist;
		return true;
	}

	return false;
}
