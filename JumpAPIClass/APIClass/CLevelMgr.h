#pragma once
class CLevel;
class CLevelMgr
{
	SINGLE(CLevelMgr);

private:
	//����� �� ������ �����ִ�.
	//�θ� ��ü �����ͷ� ������ ����� �� �ڽ��� �ִ� ��� ������ ��ü�� ����ȯ �Ҽ��ֱ� ������ 
	//�� Ÿ������ ���� �ϱⰡ ��������.
	//
	CLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];
	CLevel* m_CurLevel;

public: 
	CLevel* GetCurLevel() { return m_CurLevel; }

public:

	void init();
	void tick();
	void render(HDC _dc);
};

