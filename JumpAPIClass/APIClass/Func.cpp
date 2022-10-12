#include "pch.h"
#include "Func.h"

#include "CEventMge.h"
#include "CObj.h"

bool IsValid(CObj*& _Target)
{
	if (nullptr == _Target)
	{
		return false;
	}
	else if (_Target->IsDead())
	{
		_Target = nullptr;
		return false; 
	}

    return true;
}

void Instantiate(CObj* _NewObj, Vec2 _Pos, LAYER _Layer)
{
	_NewObj->SetPos(_Pos);

	tEvent _evn = {};
	_evn.eType = EVENT_TYPE::CREATE_OBJECT;
	_evn.wParam = (DWORD_PTR)_NewObj;
	_evn.lParam = (DWORD_PTR)_Layer;
	CEventMge::GetInst()->AddEvent(_evn);
}

void Saturate(float& _float)
{
	if (1.f < _float)
	{
		_float = 1.f;
	}
	if (0.f > _float)
	{
		_float = 0.f;
	}
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
	size_t iLen = _str.length();
	fwrite(&iLen, sizeof(size_t), 1, _pFile);
	fwrite(_str.c_str(), sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);

	wchar_t szBuff[256] = {};
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);
	_str = szBuff;
}
