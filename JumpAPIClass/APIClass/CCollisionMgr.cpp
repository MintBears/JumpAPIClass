#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"

#include "CLevel.h"
#include "CObj.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr():
	m_matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::tick()
{
	//15*15��ŭ�� ������ �˻��Ѵ�.
	for (UINT iRow = 0; iRow < (UINT)LAYER::END; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)LAYER::END; iCol++)
		{
			//������ bool���� �־����� ������ continue
			if (!(m_matrix[iRow] & (1 << iCol)))
			{
				continue;
			}
			//������ �浹�� ������ �����.
			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
		}
	}
}

void CCollisionMgr::LayerCheck(LAYER _left, LAYER _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;
	//5/2 �� 2/5�� �񱳴� �׻� �����Ƿ� �̷��� ������ ���̱� ���� �� ��ġ�̴�.
	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}
	
	//��Ʈ ��ġ��		(1 ; ���� ������ �ǹ�, << iCol : ���ʿ������� ��ĭ �����ϰ���)
	m_matrix[iRow] |= (1 << iCol);
	
	m_matrix;


}

void CCollisionMgr::CollisionBtwLayer(LAYER _left, LAYER _right)
{
	//���⼭�� ��ü�� �浹��,�浹��, �浹���� ���� ó���� �Ѵ�.
	CLevel* CorLevel = CLevelMgr::GetInst()->GetCurLevel();

	const vector<CObj*>& vecLeft = CorLevel->GetLayer(_left);
	const vector<CObj*>& vecRight = CorLevel->GetLayer(_right);

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		//���� ��ü�����°�
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		//���� ���̾ ��������, ���߰˻縦 ���ϱ�����
		size_t j = 0;
		if (_left == _right)
		{
			j = i;
		}
		
		for (; j < vecRight.size(); j++)
		{
			//���� ��ü�����°�							//�ڱ��ڽ��� ���ϴ°�
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
				continue;
			//���� ������ �浹 ���� �˻�
			CollisionID ID = {};
			ID.LeftID = vecLeft[i]->GetCollider()->GetID();
			ID.RightID = vecRight[j]->GetCollider()->GetID();
			//���� ������ �浹 Ȯ��
			map < UINT_PTR, bool >::iterator iter = m_mapPrevInfo.find(ID.id);
			if (iter == m_mapPrevInfo.end())
			{
				//���� �浹 ��ü�� 1�� ������. �׷��� �� ������ �ְ� �ٽ� �ѹ� �˻�
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}


			bool Dead = vecLeft[i]->IsDead() || vecRight[i]->IsDead();



			if (CollisionBtwCollider(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				//������ ���̴�. ��ģ �����̴�.

				//�������� �����־���.
				if (iter->second)
				{
					if (Dead)
					{
						vecLeft[i]->GetCollider()->EndOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->EndOverlap(vecLeft[i]->GetCollider());
					}
					else
					{
						vecLeft[i]->GetCollider()->OnOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnOverlap(vecLeft[i]->GetCollider());
					}

				}
				//ó�� ���ƴ�.
				else
				{
					//���� �ϳ��� dead ���¸�, �浹�� ������ ������ �Ѵ�.
					if (!Dead)
					{
						vecLeft[i]->GetCollider()->BeginOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->BeginOverlap(vecLeft[i]->GetCollider());
						iter->second = true;
					}
					
				}
				
			}
			else
			{
				if (iter->second)
				{
					//��� �� ������������
					vecLeft[i]->GetCollider()->EndOverlap(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->EndOverlap(vecLeft[i]->GetCollider());
					iter->second = false;
				}
			}
		}
	}

}

bool CCollisionMgr::CollisionBtwCollider(CCollider* _left, CCollider* _right)
{
	//���⼭�� ��ü�� �浹ü���� �Ÿ��� �浹ü ũ�� ������ ���� ���� ���� �پ����� �ƴ��� �˼���������
	//���⼭ �˻縦 �Ѵ�.
	Vec2 LeftPos = _left->GetFinalPos();
	Vec2 LeftScale = _left->GetScale();

	Vec2 RightPos = _right->GetFinalPos();
	Vec2 RightScale = _right->GetScale();

	if (fabsf(LeftPos.x - RightPos.x) > (LeftScale.x / 2.0f + RightScale.x / 2.0f))
	{
		return false;
	}
	if (fabsf(LeftPos.y - RightPos.y) > (LeftScale.y / 2.0f + RightScale.y / 2.0f))
	{
		return false;
	}

	return true;
}
