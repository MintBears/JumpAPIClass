#pragma once
#include "CRes.h"
class CSound :
    public CRes
{
public:
    CSound();
    virtual ~CSound();
private:
    virtual int Load(const wstring& _strFilePath) override;
};

