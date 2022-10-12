#pragma once
class CEntity
{
private:
	static UINT g_NextID;
private:
	wstring		m_Name;
	const UINT	m_id;
public:
	void SetName(const wstring& _name) { m_Name = _name; }
	const wstring& GetName() { return m_Name; }
	UINT GetID() { return m_id; }

public:
	CEntity();
	CEntity(const CEntity& _other);
	virtual ~CEntity();
};

