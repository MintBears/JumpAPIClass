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
    //콜백(함수주소 호출)
    TestFuncType        m_pFunc;
    //델리게이트(함수주소 + 객체주소 호출)
    CEntity*            m_pInst;
    EDLEGATE            m_pDelegateFunc;

public:

    virtual void MouseLbtnClicked() override;

    CLONE(CButton)
};

