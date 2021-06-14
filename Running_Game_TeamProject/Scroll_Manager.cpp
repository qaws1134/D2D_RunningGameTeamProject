#include "stdafx.h"
#include "Scroll_Manager.h"

IMPLEMENT_SINGLETON(CScroll_Manager)

CScroll_Manager::CScroll_Manager()
	:m_vScroll(_vec3(0.f, 0.f, 0.f))
{
}


CScroll_Manager::~CScroll_Manager()
{
}

void CScroll_Manager::Reset_Scroll(void)
{
	ZeroMemory(&m_vScroll, sizeof(_vec3));
}
