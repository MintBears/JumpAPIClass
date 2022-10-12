#include "pch.h"
#include "CAnimation.h"

#include "CCamera.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include "CObj.h"
#include "CAnimator.h"
#include "CTexture.h"

CAnimation::CAnimation(CAnimator* _pAnimator)
	: m_pAnimator(_pAnimator)
	, m_vecFrm(0)
	, m_pAtlas(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::init(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vSize, int _iMaxFrmCount, float _fDuration)
{
	SetName(_strName);
	m_pAtlas = _pAtlas;
	for (int i = 0; i < _iMaxFrmCount; i++)
	{
		tAnimFrm frm = {};
		frm.LeftTopPos = Vec2(_vLeftTop.x + (float)i * _vSize.x, _vLeftTop.y);
		frm.Duration = _fDuration;
		frm.Size = _vSize;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::tick()
{

	if (m_bFinish)
	{
		return;
	}

	m_fAccTime += DT;

	if (m_vecFrm[m_iCurFrm].Duration < m_fAccTime)
	{
		++m_iCurFrm;
		m_fAccTime = 0.f;
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = (int)m_vecFrm.size() - 1;
			m_bFinish = true;
		}
	}



	//if (m_vecFrm.size() <= m_iCurFrm)
	//{
	//	m_iCurFrm = 0;
	//}

	m_iCurFrm;
}

void CAnimation::render(HDC _dc)
{

	CObj* pOwnerObj = m_pAnimator->GetOwner();

	Vec2 Pos = CCamera::GetInst()->GetRenderPos(pOwnerObj->GetPos());
	Vec2 Size = pOwnerObj->GetScale();

	tAnimFrm frm = m_vecFrm[m_iCurFrm];
	
	TransparentBlt(_dc
		, (int)(Pos.x - frm.Size.x / 2.0f), (int)(Pos.y - frm.Size.y / 2.0f)
		, (int)frm.Size.x, (int)frm.Size.y
		, m_pAtlas->GetDC()
		, (int)frm.LeftTopPos.x, (int)frm.LeftTopPos.y
		, (int)frm.Size.x, (int)frm.Size.y
		, RGB(255,0,255));

}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath =  CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	//파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNum =  _wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	//입출력 실패시
	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Save 실패, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 저장실패", MB_OK);
		return;
	}

	//애니메이션 이름 저장
	fwprintf_s(pFile, L"\n");
	fwprintf_s(pFile, L"[Animation_Name]\n");
	fwprintf_s(pFile, GetName().c_str());
	fwprintf_s(pFile, L"\n\n");


	//
	////아틀라스 키값 저장
	//SaveWString(m_pAtlas->GetKey(), pFile);
	fwprintf_s(pFile, L"[Animation_Key]\n");
	fwprintf_s(pFile, m_pAtlas->GetKey().c_str());
	fwprintf_s(pFile, L"\n\n");
	//
	////아틀라스 상대경로 저장
	//SaveWString(m_pAtlas->GetRelativePath(), pFile);
	fwprintf_s(pFile, L"[Animation_RelativePath]\n");
	fwprintf_s(pFile, m_pAtlas->GetRelativePath().c_str());
	fwprintf_s(pFile, L"\n\n");

	//프레임 정보 저장
	wchar_t szNum[50] = {};
	fwprintf_s(pFile, L"[Frame_Count]\n");

	size_t iFrmCount = m_vecFrm.size();
	_itow_s((int)iFrmCount, szNum, 50, 10);

	fwprintf_s(pFile, szNum);
	fwprintf_s(pFile, L"\n\n");

	for (size_t i = 0; i < iFrmCount; i++)
	{
		//LEFT_TOP
		fwprintf_s(pFile, L"[%zd_Frame]\n", i);
		fwprintf_s(pFile, L"[LEFT_TOP]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].LeftTopPos.x, m_vecFrm[i].LeftTopPos.y);

		//SIZE
		fwprintf_s(pFile, L"[SIZE]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].Size.x, m_vecFrm[i].Size.y);
		//OFFSET
		fwprintf_s(pFile, L"[OFFSET]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].Offset.x, m_vecFrm[i].Offset.y);
		//DURATION
		fwprintf_s(pFile, L"[DURATION]\n");
		fwprintf_s(pFile, L"%.2f\n", m_vecFrm[i].Duration);
		fwprintf_s(pFile, L"\n");
	}
	//fwrite(&iFrmCount, sizeof(size_t), 1, pFile);
	//fwrite(m_vecFrm.data(), sizeof(tAnimFrm), m_vecFrm.size(), pFile);
	//fwprintf_s(pFile, L"\n\n");






	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	//파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	//입출력 실패시
	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Load 실패, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 불러오기실패", MB_OK);
		return;
	}

	size_t iFrameCount = 0;
	wstring strKey, strRelativePath;
	while (true)
	{
		wchar_t szBuffer[256] = {};
		fwscanf_s(pFile, L"%s", szBuffer, 256);

		if (!wcscmp(szBuffer, L"[Animation_Name]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			SetName(szBuffer);
		}

		else if (!wcscmp(szBuffer, L"[Animation_Key]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strKey = szBuffer;
		}

		else if (!wcscmp(szBuffer, L"[Animation_RelativePath]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strRelativePath = szBuffer;
		}

		else if (!wcscmp(szBuffer, L"[Frame_Count]"))
		{
			fwscanf_s(pFile, L"%zd", &iFrameCount); 

			for (size_t i = 0; i < iFrameCount; i++)
			{
				tAnimFrm frm = {};

				while (true)
				{
					wchar_t szBuffer[256] = {};
					fwscanf_s(pFile, L"%s", szBuffer, 256);

					if (!wcscmp(szBuffer, L"[LEFT_TOP]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.LeftTopPos.x, &frm.LeftTopPos.y);
					}
					else if (!wcscmp(szBuffer, L"[SIZE]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.Size.x, &frm.Size.y);
					}
					else if (!wcscmp(szBuffer, L"[OFFSET]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.Offset.x, &frm.Offset.y);
					}
					else if (!wcscmp(szBuffer, L"[DURATION]"))
					{
						fwscanf_s(pFile, L"%f", &frm.Duration);
						break;
					}
				}
				m_vecFrm.push_back(frm);
			}
			break;
		}
	}

	/*
	size_t iFrmCount = 0;
	fread(&iFrmCount, sizeof(size_t), 1, pFile);
	for (size_t i = 0; i < iFrmCount; i++)
	{
		tAnimFrm frm = {};
		fread(&frm, sizeof(tAnimFrm), 1, pFile);
		m_vecFrm.push_back(frm);
	}



	wstring strName, strKey, strRelativePath;
	LoadWString(strName, pFile);
	SetName(strName);
	
	LoadWString(strKey, pFile);
	LoadWString(strRelativePath, pFile);
	*/

	m_pAtlas = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);

	fclose(pFile);
}
