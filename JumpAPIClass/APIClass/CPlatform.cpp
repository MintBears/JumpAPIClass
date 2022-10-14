#include "pch.h"
#include "CPlatform.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CRigidbody.h"

CPlatform::CPlatform()
{
	CreateCollider();

	GetCollider()->SetScale(Vec2(400.f, 50.f));
}

CPlatform::~CPlatform()
{
}

void CPlatform::BeginOverlap(CCollider* _Other)
{
	//dynamic_cast : 부모 클래스의 포인터에서 자식 클래스의 포인터로 안전하게 다운 캐스팅 해주는 연산자 입니다.
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_Other->GetOwner());
	if (nullptr == pPlayer)
		return;
	
	pPlayer->GetCRigidbody()->SetGround(true);
}

void CPlatform::OnOverlap(CCollider* _Other)
{

}

void CPlatform::EndOverlap(CCollider* _Other)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_Other->GetOwner());
	if (nullptr == pPlayer)
		return;

	pPlayer->GetCRigidbody()->SetGround(false);
}
