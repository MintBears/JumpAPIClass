#pragma once
#include "CEntity.h"
class CRes :
    public CEntity
{

public:
    CRes();
    virtual ~CRes();

private:

    wstring         m_Key;
    wstring         m_RelativePath;

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }

private:
    void SetKey(const wstring& _key) { m_Key = _key; }
    void SetRelativePath(const wstring& _RelativePath) { m_RelativePath = _RelativePath; }


protected:
    virtual int Load(const wstring& _strFilePath) = 0;

    friend class CResMgr;

};

