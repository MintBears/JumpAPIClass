#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator(CObj* _Owner)
	: CComponent(_Owner)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();

	for ( ; iter != m_mapAnim.end(); iter++)
	{
		delete iter ->second;
	}
}

void CAnimator::tick()
{
	m_bRepeat;
	if (nullptr == m_pCurAnim)
	{
		return;
	}

	if (m_pCurAnim->IsFinish() && m_bRepeat)
	{
		m_pCurAnim->Reset();
	}
	m_pCurAnim->tick();
}

void CAnimator::render(HDC _dc)
{
	if (nullptr == m_pCurAnim)
	{
		return;
	}
	m_pCurAnim->render(_dc);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vSize, int _iMaxFrmCount, float _fDuration)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(!pAnim);

	pAnim = new CAnimation(this);

	pAnim->init(_strName, _pAtlas, _vLeftTop, _vSize, _iMaxFrmCount, _fDuration);

	m_mapAnim.insert(make_pair( _strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);
	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}

CAnimation* CAnimator::LoadAnimation(const wstring& _strRelativePath)
{

	CAnimation* pAnim = new CAnimation(this);

	pAnim->Load(_strRelativePath);

	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));

	return pAnim;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		MessageBox(nullptr, L"해당 Animation 없음", L"Animation 재생 오류", MB_OK);
		return;
	}

	m_pCurAnim = pAnim;
	m_pCurAnim->Reset();
	m_bRepeat = _bRepeat;
}

