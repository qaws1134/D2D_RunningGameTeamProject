#include "stdafx.h"
#include "FieldHurdle.h"
#include "Single_Texture.h"
#include "Multi_Texture.h"
CFieldHurdle::CFieldHurdle() : iCX(0),iCY(0)
{
}


CFieldHurdle::~CFieldHurdle()
{
}

HRESULT CFieldHurdle::Ready_Object(void)
{
	switch (m_eID)
	{
	case HURDLEID::FLOOR:
		iCX = 124;
		iCY = 140;
		break;
	case HURDLEID::FLOOR2F:
		iCX = 129;
		iCY = 52;
		break;
	case HURDLEID::LOWHILL:
		iCX = 87;
		iCY = 118;
		break;
	case HURDLEID::HIGHHILL:
		iCX = 125;
		iCY = 227;
		break;
	case HURDLEID::BULLET:
		iCX = 202;
		iCY = 117;
		break;
	case HURDLEID::CELLING:
		iCX = 165;
		iCY = 493;
		break;
	default:
		break;
	}

	return S_OK;
}

int CFieldHurdle::Update_Object(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	const TEXINFO* pTexInfo = 
		CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);



	return OBJ_NOEVENT;
}

void CFieldHurdle::LateUpdate_Object(void)
{
}

void CFieldHurdle::Render_Object(void)
{
}

void CFieldHurdle::Release_Object(void)
{
}
