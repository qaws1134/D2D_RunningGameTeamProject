#include "stdafx.h"
#include "Line.h"
#include "Scroll_Manager.h"

CLine::CLine()
{
}


CLine::~CLine()
{
	Release();
}

void CLine::Initialize()
{
}

void CLine::Render( )
{
	_vec3 Scroll = CScroll_Manager::Get_Instance()->Get_Scroll();
	CGraphic_Dev::Get_Instance()->Get_Sprite()->End();

	D3DXVECTOR2 vLinePos[2] = { { m_tInfo.LPos.x- Scroll.x,m_tInfo.LPos.y }, {m_tInfo.RPos.x - Scroll.x,m_tInfo.RPos.y} };
	CGraphic_Dev::Get_Instance()->Get_Line()->Draw(vLinePos, 2, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGraphic_Dev::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

}

void CLine::Release()
{
}
