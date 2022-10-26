#pragma once
#include "CUI.h"

class CEditorLevel;
class CTexture;

typedef void(*TestFuncType)(void);

typedef void (CEntity::* DELEGATE)(void);

class CButton :
    public CUI
{
public:
    CButton();
    ~CButton();

private:
    CTexture*           m_pPressedTex;              //누른상태의 이미지값
    CTexture*           m_pHighlightTex;            //마우스가 위에 올라가있을때의 이미지값
    //콜백(함수주소 호출)
    TestFuncType        m_pFunc;
    //델리게이트(함수주소 + 객체주소 호출)
    CEntity*            m_pInst;
    DELEGATE            m_pDelegateFunc;            //버튼이 누르면 작동할 내용
public:

    void SetCallBack(TestFuncType _pCallBack) { m_pFunc = _pCallBack; }         //전역으로 선언하고 버튼이 누르면 작동할 내용 입력받기
    void SetDelegate(CEntity* _pInst, DELEGATE _Func)                           //버튼이 누르면 작동할 내용 입력받기
    {
        m_pInst = _pInst;
        m_pDelegateFunc = _Func;
    }
    void SetHighlightTex(CTexture* _pTex) { m_pHighlightTex = _pTex; }          //마우스가 위에 올라가있을때의 이미지값 입력받기
    void SetPressedTex(CTexture* _pTex) { m_pPressedTex = _pTex; }              //누른상태의 이미지값 입력받기

public:
    virtual void render(HDC _dc) override;
    CLONE(CButton)

public:

    virtual void MouseLbtnClicked() override;                                   //마우스위치에 따른 버튼의 상태함수
};

