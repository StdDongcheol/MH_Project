
#include "ObjectManager.h"
#include "Mernos.h"

DEFINITION_SINGLE(CObjectManager)

CObjectManager::CObjectManager()	:
	m_CheckType(Check_Type::StageToLoading),
	m_IsCheck(false)
{

}

CObjectManager::~CObjectManager()
{

}

bool CObjectManager::Init()
{
	return true;
}

void CObjectManager::SaveCheckToPointFunc(Check_Type Type)
{
	m_CheckType = Type;

	m_IsCheck = true;
}

void CObjectManager::LoadCheckToPointFunc(CMernos* Obj)
{
	// ����Ȱ� ���ٸ� �ε��Ұ� ���ٴ� �ǹ��̱⶧���� ����
	if (!m_IsCheck)
		return;

	Obj->SetCheckToPointType(m_CheckType);

	// �ε带 �Ϸ��ߴٸ� üũ�� �ٽ� false�� ������
	m_IsCheck = false;
}
