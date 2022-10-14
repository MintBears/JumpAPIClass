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
	//dynamic_cast : �θ� Ŭ������ �����Ϳ��� �ڽ� Ŭ������ �����ͷ� �����ϰ� �ٿ� ĳ���� ���ִ� ������ �Դϴ�.
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
