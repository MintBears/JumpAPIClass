#pragma once

class CObj;
bool IsValid(CObj*& _pTarget);

void Instantiate(CObj* _NewObj, Vec2 _Pos, LAYER _Layer);

void Saturate(float& _float);
void SaveWString(const wstring& _str, FILE* _pFile);
void LoadWString(wstring& _str, FILE* _pFile);