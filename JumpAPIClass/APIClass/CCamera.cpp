#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CTexture.h"

CCamera::CCamera()
	: m_pBlindTex(nullptr)
	, m_fRatio(0.0f)
	, m_fAccTime(0.0f)
	, m_fMaxTime(0.0f)
	, m_fRange(0.0f)
	, m_fShakeSpeed(0.0f)
	, m_bCamShake(false)
	, m_fShakeDir(1.0f)

{ 
	POINT ptResolution = CEngine::GetInst()->GetResolution();

	m_pBlindTex = CResMgr::GetInst()->CreatTexture(L"BlindTex", ptResolution.x, ptResolution.y);
}

CCamera::~CCamera()
{
}


void CCamera::tick()
{
	if (IsPressed(KEY::W))
		m_Look.y -= 200.f * DT;
	if (IsPressed(KEY::S))
		m_Look.y += 200.f * DT;
	if (IsPressed(KEY::A))
		m_Look.x -= 200.f * DT;
	if (IsPressed(KEY::D))
		m_Look.x += 200.f * DT;
	
	Vec2 Resolution = CEngine::GetInst()->GetResolution();
	Resolution /= 2.0f;
	m_Diff = m_Look + m_vOffset - Resolution;

	//ī�޶� ������ ȿ��
	CameraEffect();

	//ī�޶� ��鸲 ȿ��
	CameraShake();
}

void CCamera::render(HDC _dc)
{
	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = 0;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255 * m_fRatio);
	//tBlend.SourceConstantAlpha = 255;

	if (m_fRatio < 0.001f)
	{
		return;
	}

	AlphaBlend(_dc, 0
		, 0
		, m_pBlindTex->Widht()
		, m_pBlindTex->Height()
		, m_pBlindTex->GetDC()
		, 0, 0
		, m_pBlindTex->Widht()
		, m_pBlindTex->Height()
		, tBlend);
}

void CCamera::FadeOut(float _fTerm)
{
	tCamEffect effect = {};
	effect.m_eCurEffect = CAMERA_EFFECT::FADE_OUT;
	effect.m_fAccTime = 0.0f;
	effect.m_fMaxTime = _fTerm;
	m_listCamEffect.push_back(effect);
}

void CCamera::FadeIn(float _fTerm)
{
	tCamEffect effect = {};

	effect.m_eCurEffect = CAMERA_EFFECT::FADE_IN;
	effect.m_fAccTime = 0.0f;
	effect.m_fMaxTime = _fTerm;

	m_listCamEffect.push_back(effect);

}

//����ũ �ʱ�ȭ
void CCamera::CameraShake(float _fRange, float _fSpeed, float _fTerm)
{
	m_fAccTime = 0.0f;
	m_fMaxTime = _fTerm;
	m_fRange = _fRange;
	m_fShakeDir = _fSpeed;
	m_fShakeDir = 1.0f;
	m_bCamShake = true;
}

//����ũ ���� ó��
void CCamera::CameraEffect()
{
	if (m_listCamEffect.empty())
	{
		return;
	}

	tCamEffect& effect = m_listCamEffect.front();

	effect.m_fAccTime += DT;
	if (effect.m_fAccTime >= effect.m_fMaxTime)
	{
		m_listCamEffect.pop_front();
		return;
	}

	m_fRatio = effect.m_fAccTime / effect.m_fMaxTime;
	if (effect.m_eCurEffect == CAMERA_EFFECT::FADE_IN)
	{
		m_fRatio = 1.0f - m_fRatio;
	}
}

void CCamera::CameraShake()
{
	//����ũ�� Ȱ��ȭ���������� �ٷ� ����
	if (!m_bCamShake)
	{
		return;
	}

	//�ð��� �� ƽ���� ������Ű�� �����Ǹ� ��鸲 ����
	m_fAccTime += DT;
	if (m_fMaxTime <= m_fAccTime)
	{
		m_bCamShake = false;
		m_vOffset = Vec2(0.f, 0.f);
	}

	//ƽ���� �̵��� �Ÿ��� ������, ������ ������ ���� ��ȯ�� �ϰ� �Ѵ�.
	m_vOffset.y += DT * m_fShakeSpeed * m_fShakeDir;
	if (m_fRange < fabs(m_vOffset.y))
	{
		//���� �Ѿ� ���⶧���� ������ �ؾߵȴ�.
		m_vOffset.y = m_fRange * m_fShakeDir;
		m_fShakeDir *= -1;
	}
}
