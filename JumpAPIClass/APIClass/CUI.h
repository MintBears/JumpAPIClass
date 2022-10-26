#pragma once
#include "CObj.h"
class CUI :
    public CObj
{
public:
    CUI();
    CUI(const CUI& _other);
    ~CUI();

private:

    Vec2            m_vFinalPos;        //최종 ui위치

    bool            m_bLbtnDown;        //좌클릭을했는가?
    bool            m_bMouseOn;         //마우스가 위에?
    bool            m_bCmrAfctd;        //카메라를 따라가는가?

    vector<CUI*>    m_vecChildUI;       //내 ui에 자식들을 답는 변수
    CUI*            m_pParentUI;        //부모UI

    CTexture* m_pIdleTex;               //UI기본 이미지

public:

    Vec2 GetFinalPos() { return m_vFinalPos; }                      //최종위치가져오기

    bool IsMouseOn() { return m_bMouseOn; }                         //마우스가 위에있는 것의 대한 bool값 반환
    bool IsLbtnDown() { return m_bLbtnDown; }                       //좌클랙에 대한 bool값 반환

    CUI* GetParentUI() { return m_pParentUI; }                      //부모UI가져오기
    CTexture* GetIdleTex() { return m_pIdleTex; }                   //자신의 Idle이미지 가져오기

    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }       //변경할수 없는 자식UI객체정보 가져오기

    void SetCAmeraAffected(bool _bSet) { m_bCmrAfctd = _bSet; }     //카메라를 따라가는 bool값의 대해 입력받기
    void SetIdleTex(CTexture* _pTex);                               //Idle이미지 입력받기

    void AddChildUI(CUI* _pChildUI)                                 //모든 자식 UI정보 담기
    {
        _pChildUI->m_pParentUI = this;
        m_vecChildUI.push_back(_pChildUI);
    }

public:
    virtual void tick();
    virtual void render(HDC _dc);
    void render_childUI(HDC _dc);

    CLONE(CUI)

public:
    virtual void MouseLbtnDown() { m_bLbtnDown = true; };
    virtual void MouseLbtnClicked() {};
    virtual void MouseOn() {};

private:
    void MouseOnCheck();

public:

    friend class CUIMgr;

};

