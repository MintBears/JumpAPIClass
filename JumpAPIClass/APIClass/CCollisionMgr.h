#pragma once

#define MAKE_COLID(left, right) (LEFT_ALT_PRESSED << 32) | right

union CollisionID
{
	struct
	{
		UINT LeftID;
		UINT RightID;
	};

	UINT_PTR id;
};


class CCollider;
class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	WORD					m_matrix[(UINT)LAYER::END];
	//id���� �߳� ���߳Ľĺ��ϱ����� bool��
	map<UINT_PTR, bool>		m_mapPrevInfo;	//���� �����ӿ� �� �浹ü�� �浹����

public:
	void Clear() 
	{
		for (int i = 0; i < (UINT)LAYER::END; i++)
		{
			m_matrix[i] = 0;
		}
	}
public:
	void tick();
	void LayerCheck(LAYER _left, LAYER _right);
	

private:
	void CollisionBtwLayer(LAYER _left, LAYER _right);
	bool CollisionBtwCollider(CCollider* _left, CCollider* _right);

};

