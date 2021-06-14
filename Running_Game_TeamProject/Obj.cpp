#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	:m_bDead(false), m_bIsCollied(false)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
}

CObj::CObj(const INFO & rInfo)
	: m_tInfo(rInfo), m_bDead(false), m_bIsCollied(false)
{
}

CObj::CObj(const CObj & rhs)
	: m_tInfo(rhs.m_tInfo), m_bDead(false), m_bIsCollied(false)
{
}


CObj::~CObj()
{
}

void CObj::Ready_Rectangle(void)
{
	// ÁÂ»ó
	m_tInfo.m_vPoint[0] = _vec3(-m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f);
	// ¿ì»ó
	m_tInfo.m_vPoint[1] = _vec3(m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f);
	// ¿ìÇÏ
	m_tInfo.m_vPoint[2] = _vec3(m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f);
	// ÁÂÇÏ
	m_tInfo.m_vPoint[3] = _vec3(-m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f);
}

