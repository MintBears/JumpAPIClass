#pragma once
#include "CEntity.h"

#include "CAI.h"
#include "CObj.h"
class CAI;

class CState :
    public CEntity
{
public:
    CState();
    ~CState();
private:
    CAI*            m_pOwnerAI;

public:
    CAI* GetOwnerAI() { return m_pOwnerAI; }
    CObj* GetOwnerObj() { return m_pOwnerAI->GetOwner(); }

    void ChangeState(const wchar_t* _strStateName);
public:
    virtual void finaltick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

    CState* Clone() = 0;

    friend class CAI;
};

