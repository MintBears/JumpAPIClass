#pragma once
#include "CUI.h"

class CEditorLevel;
typedef void(*TestFuncType)(void);

typedef void (CEntity::* EDLEGATE)(void);

class CButton :
    public CUI
{
public:
    CButton();
    ~CButton();

private:
    //�ݹ�(�Լ��ּ� ȣ��)
    TestFuncType        m_pFunc;
    //��������Ʈ(�Լ��ּ� + ��ü�ּ� ȣ��)
    CEntity*            m_pInst;
    EDLEGATE            m_pDelegateFunc;

public:

    virtual void MouseLbtnClicked() override;

    CLONE(CButton)
};

