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
    CTexture*           m_pPressedTex;              //���������� �̹�����
    CTexture*           m_pHighlightTex;            //���콺�� ���� �ö��������� �̹�����
    //�ݹ�(�Լ��ּ� ȣ��)
    TestFuncType        m_pFunc;
    //��������Ʈ(�Լ��ּ� + ��ü�ּ� ȣ��)
    CEntity*            m_pInst;
    DELEGATE            m_pDelegateFunc;            //��ư�� ������ �۵��� ����
public:

    void SetCallBack(TestFuncType _pCallBack) { m_pFunc = _pCallBack; }         //�������� �����ϰ� ��ư�� ������ �۵��� ���� �Է¹ޱ�
    void SetDelegate(CEntity* _pInst, DELEGATE _Func)                           //��ư�� ������ �۵��� ���� �Է¹ޱ�
    {
        m_pInst = _pInst;
        m_pDelegateFunc = _Func;
    }
    void SetHighlightTex(CTexture* _pTex) { m_pHighlightTex = _pTex; }          //���콺�� ���� �ö��������� �̹����� �Է¹ޱ�
    void SetPressedTex(CTexture* _pTex) { m_pPressedTex = _pTex; }              //���������� �̹����� �Է¹ޱ�

public:
    virtual void render(HDC _dc) override;
    CLONE(CButton)

public:

    virtual void MouseLbtnClicked() override;                                   //���콺��ġ�� ���� ��ư�� �����Լ�
};

