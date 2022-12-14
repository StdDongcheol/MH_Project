#pragma once
#include "SceneComponent.h"
class CLandScape :
	public CSceneComponent
{
	friend class CGameObject;
	friend class CCameraManager;

protected:
	CLandScape();
	CLandScape(const CLandScape& com);
	virtual ~CLandScape();

protected:
	CSharedPtr<class CStaticMesh>	m_Mesh;
	CSharedPtr<class CPickingComputeShader>	m_PickingCS;
	class CLandScapeConstantBuffer* m_CBuffer;
	class CPickingConstantBuffer* m_PickingCBuffer;
	class CStructuredBuffer* m_InputSBuffer;
	class CStructuredBuffer* m_OutputSBuffer;
	PickingInputDesc* m_InputDesc;
	PickingOutputDesc* m_OutputDesc;
	ID3D11Buffer* m_Buffer;
	std::vector<Vertex3DSplatting>		m_vecVtx;
	std::vector<Vector3>		m_vecPos;
	std::vector<unsigned int>	m_vecIndex;
	std::vector<Vector3>		m_vecFaceNormal;
	std::vector<CSharedPtr<class CMaterial>> m_vecMaterialSlot;
	Vector3	m_Min;
	Vector3	m_Max;
	Vector3	m_DDTPos;
	int		m_CountX;
	int		m_CountZ;
	int		m_SelectMap;
	unsigned int m_VertexSize;
	float	m_BrushHeight;
	float	m_BrushSpaltting;

public:
	void SetBrushHeightScale(float Scale)
	{
		m_BrushHeight = Scale;
	}

	void SetBrushSplattingScale(float Scale)
	{
		m_BrushSpaltting = Scale;
	}

	void SetCountX(int X)
	{
		m_CountX = X;
	}

	void SetCountZ(int Z)
	{
		m_CountZ = Z;
	}

	void SelectMap(int Map)
	{
		m_SelectMap = Map;
	}

public:
	int GetCountX()	const
	{
		return m_CountX;
	}

	int GetCountZ()	const
	{
		return m_CountZ;
	}

	Vector3 GetDDTPos()	const
	{
		return m_DDTPos;
	}

	const Vector3& GetMin()	const
	{
		return m_Min;
	}

	const Vector3& GetMax()	const
	{
		return m_Max;
	}

	CMaterial* GetMaterial(int Index = 0)    const
	{
		return m_vecMaterialSlot[Index];
	}

public:
	void CreateLandScape(const std::string& Name, int CountX, int CountZ, const TCHAR* HeightMap = nullptr, const std::string& PathName = TEXTURE_PATH);
	void SetMaterial(class CMaterial* Material, int Index = 0);
	void SetMaterial(const std::string& Name, int Index = 0);
	void AddMaterial(class CMaterial* Material);
	void AddMaterial(const std::string& Name);
	void SetDetailLevel(float Level);
	void SetSplatCount(int Count);
	void CreateNavigationData(class CNavigationMesh* NavMesh);
	void ReleaseMesh();

public:
	void PlayBrush(float DeltaTime, bool Up);
	void PlaySplatting(float DeltaTime, bool Draw, int TextureType);

public:
	int GetBrushType()	const;
	Vector3 GetBrushLocation()	const;
	float GetBrushRange()	const;
	Vector3 GetBrushColor()	const;

public:
	void SetBrushType(int Type);
	void SetBrushType(Brush_Type Type);
	void SetBrushLocation(const Vector3& Location);
	void SetBrushRange(float Range);
	void SetBrushColor(const Vector3& Color);

public:
	float GetHeight(const Vector3& Pos);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void RenderShadowMap();
	virtual void PostRender();
	virtual CLandScape* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);


private:
	void ComputeNormal();
	void ComputeTangent();
	bool ComputePicking(Vector3* Pos);
};

