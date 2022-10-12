#include "pch.h"
#include "CEntity.h"

UINT CEntity::g_NextID = 0;

CEntity::CEntity()
	: m_Name()
	, m_id(g_NextID++)
{
}

CEntity::CEntity(const CEntity& _other)
	: m_Name(_other.m_Name)
	, m_id(_other.g_NextID++)
{
}

CEntity::~CEntity()
{
}
