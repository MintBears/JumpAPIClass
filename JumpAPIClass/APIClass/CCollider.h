#pragma once
#include "CComponent.h"


class CCollider :
    public CComponent
{
public:
    CCollider(CObj* _Owner);
    virtual ~CCollider();

private:
    //�߰��� ������ ũ��
    Vec2        m_OffsetPos;
    //�������� ���� ���� ũ��
    Vec2        m_FinalPos;
    //�浹ü ������ ũ��
    Vec2        m_Scale;

    int        m_OverlapCount;

public:
    void SetOffsetPos(Vec2 _OffsetPos) { m_OffsetPos = _OffsetPos; }
    Vec2 GetOffsetPos() { return m_OffsetPos; }
    
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    Vec2 GetScale() { return m_Scale; }

    Vec2 GetFinalPos() { return m_FinalPos; }

    

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    void BeginOverlap(CCollider* _Other);
    void OnOverlap(CCollider* _Other);
    void EndOverlap(CCollider* _Other);
};

