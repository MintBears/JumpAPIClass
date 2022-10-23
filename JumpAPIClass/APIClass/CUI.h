#pragma once
#include "CObj.h"
class CUI :
    public CObj
{
public:
    CUI();
    ~CUI();

private:
    bool            m_bLbtnDown;
    bool            m_bMouseOn;

    bool            m_bCmrAfctd;

public:

    void SetCAmeraAffected(bool _bSet) { m_bCmrAfctd = _bSet; }
    bool IsMouseOn() { return m_bMouseOn; }

public:

    virtual void tick();
    virtual void render(HDC _dc);

    CLONE(CUI)


public:
    virtual void MouseLbtnDown() { m_bLbtnDown = true; };
    virtual void MouseLbtnClicked() {};
    virtual void MouseOn() {};

private:
    void MouseOnCheck();

    friend class CUIMgr;

};

