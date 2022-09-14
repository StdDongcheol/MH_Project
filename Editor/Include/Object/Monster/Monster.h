#include "GameObject/GameObject.h"

#pragma once
class CMonster : 
    public CGameObject
{
	friend class CScene;

protected:
    float CurYRot;
    bool IsMoving;
    Transform_State m_State=Transform_State::None;
protected:
    float CalAngle(Vector3 V)
    {
        return V.Angle(Vector3(0, 0, -1));
    }

    void Move(Vector3 Dest);
    void RotateTo(Vector3 v);

	
};

