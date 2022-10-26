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

    Vec2            m_vFinalPos;        //���� ui��ġ

    bool            m_bLbtnDown;        //��Ŭ�����ߴ°�?
    bool            m_bMouseOn;         //���콺�� ����?
    bool            m_bCmrAfctd;        //ī�޶� ���󰡴°�?

    vector<CUI*>    m_vecChildUI;       //�� ui�� �ڽĵ��� ��� ����
    CUI*            m_pParentUI;        //�θ�UI

    CTexture* m_pIdleTex;               //UI�⺻ �̹���

public:

    Vec2 GetFinalPos() { return m_vFinalPos; }                      //������ġ��������

    bool IsMouseOn() { return m_bMouseOn; }                         //���콺�� �����ִ� ���� ���� bool�� ��ȯ
    bool IsLbtnDown() { return m_bLbtnDown; }                       //��Ŭ���� ���� bool�� ��ȯ

    CUI* GetParentUI() { return m_pParentUI; }                      //�θ�UI��������
    CTexture* GetIdleTex() { return m_pIdleTex; }                   //�ڽ��� Idle�̹��� ��������

    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }       //�����Ҽ� ���� �ڽ�UI��ü���� ��������

    void SetCAmeraAffected(bool _bSet) { m_bCmrAfctd = _bSet; }     //ī�޶� ���󰡴� bool���� ���� �Է¹ޱ�
    void SetIdleTex(CTexture* _pTex);                               //Idle�̹��� �Է¹ޱ�

    void AddChildUI(CUI* _pChildUI)                                 //��� �ڽ� UI���� ���
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

