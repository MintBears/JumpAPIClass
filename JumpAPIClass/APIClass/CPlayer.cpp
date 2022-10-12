#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEventMge.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include "CLevel.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidbody.h"

#include "CMissile.h"



CPlayer::CPlayer()
	: m_fSpeed(200.f)

{
	CreateCollider();
	CreateAnimator();
	CreatRigidbody();
	
	GetCollider()->SetOffsetPos(Vec2(0.f, -50.f));
	GetCollider()->SetScale(Vec2(150.f, 150.f));


	CTexture* tex = CResMgr::GetInst()->LoadTexture(L"Player", L"texture\\character_001_isaac.bmp");

	//GetCAnimator()->CreateAnimation(L"HeadMove", tex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), 6, 0.5f);
	//
	//GetCAnimator()->FindAnimation(L"HeadMove")->Save(L"animation\\HeadMove.anim");

	GetCAnimator()->LoadAnimation(L"animation\\HeadMove.anim");

	GetCRigidbody()->SetVelocityLimit(200.0f);
	GetCRigidbody()->SetFriction(100.f);
}

CPlayer::~CPlayer()
{

}

void CPlayer::tick()
{
	Vec2 vPos = GetPos();

	//������ : ���� ������ Ű���¸� �� tick ���� Ȯ���� �ؾߵǴ� ��Ȳ�̴�.
	//�ذ� : �̰� ���������� �������� �޴����� ���� �����ߵȴ�.
	if (IsPressed(KEY::LEFT))
	{
		GetCRigidbody()->AddForce(Vec2(-200.f, 0.f));
		//vPos.x -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::RIGHR))
	{
		GetCRigidbody()->AddForce(Vec2(200.f, 0.f));
		//vPos.x += m_fSpeed * DT;
	}

	if (IsPressed(KEY::UP))
	{
		GetCRigidbody()->AddForce(Vec2(0.f, -200.f));
		//vPos.y -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::DOWN))
	{
		GetCRigidbody()->AddForce(Vec2(0.f, 200.f));
		//vPos.y += m_fSpeed * DT;
	}

	if (IsTap(KEY::SPACE))
	{
		//CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

		for (int i = 0; i < 3; i++)
		{
			CMissile* Missile = new CMissile;
			//Missile->SetPos(GetPos());
			Missile->SetScale(Vec2(20.F, 20.f));
			Missile->SetSpeed(400.f);
			Missile->SetDir(45.f + (45.f * (float)i));
			//�ٷ� ������ �߰��Ѵ�.
			//CurLevel->AddObject(Missile, LAYER::PLAYER_PROJECTILE);
			//����ٰ� ������ tick���� ȣ���� ������Ʈ�� �ٷ� ó�����ϰ� Event�� ���� ó���Ѵ�.
			//_evn.eType : �̺�Ʈ Ÿ�� �����ϰ�, _evn.wParam : �̺�Ʈ ���� �����ϰ�, AddEvent(_evn) : �̺�Ʈ�޴����� �ִ´�.
 			//tEvent _evn = {};
			//_evn.eType = EVENT_TYPE::CREATE_OBJECT;
			//_evn.wParam = (DWORD_PTR)Missile;
			//_evn.lParam = (DWORD_PTR)LAYER::PLAYER_PROJECTILE;
			//CEventMge::GetInst()->AddEvent(_evn);
			//�̰͵��� �Լ�ȭ
			Instantiate(Missile, GetPos(), LAYER::PLAYER_PROJECTILE);
		}
	}

	if (IsTap(KEY::UP))
		GetCAnimator()->Play(L"HeadMove", true);

	SetPos(vPos);

	CObj::tick();
}

void CPlayer::render(HDC _dc)
{
	//Vec2 Pos = CCamera::GetInst()->GetRenderPos(GetPos());
	//Vec2 Size = GetScale();
	//
	//Vec2 LeftTop = Vec2(Pos.x - m_Texture->Widht() / 2.0f, Pos.y - m_Texture->Height() / 2.0f);
	//
	////HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, (HBRUSH)GetStockObject(NULL_BRUSH));
	////
	////Rectangle(_dc, (int)(Pos.x - Size.x / 2.f)
	////			 , (int)(Pos.y - Size.y / 2.f)
	////			 , (int)(Pos.x + Size.x / 2.f)
	////			 , (int)(Pos.y + Size.y / 2.f));
	////
	////SelectObject(_dc, hOriginBrush);
	//
	////BitBlt(_dc, (int)LeftTop.x, (int)LeftTop.y
	////            , (int)m_Texture->Widht(), (int)m_Texture->Height()
	////            , m_Texture->GetDC()
	////            , 0, 0, SRCCOPY);
	//
	//TransparentBlt(_dc, (int)LeftTop.x, (int)LeftTop.y
	//						, (int)m_Texture->Widht(), (int)m_Texture->Height()
	//						, m_Texture->GetDC()
	//						, 0, 0
	//						, (int)m_Texture->Widht(), (int)m_Texture->Height(), RGB(255,0,255));

	
	
	CObj::render(_dc);
}

void CPlayer::BeginOverlap(CCollider* _Other)
{
	
}

void CPlayer::OnOverlap(CCollider* _Other)
{
}

void CPlayer::EndOverlap(CCollider* _Other)
{
}
