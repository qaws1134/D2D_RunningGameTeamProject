#include "stdafx.h"
#include "FieldHurdle.h"
#include "Texture_Manager.h"

CFieldHurdle::CFieldHurdle(): byDrawID(0),byOption(0)
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
		m_tInfo.vSize.x = 124.f;
		m_tInfo.vSize.y = 140.f;
		
		break;
	case HURDLEID::FLOOR2F:
		m_tInfo.vSize.x = 129.f;
		m_tInfo.vSize.y = 52.f;
		break;
	case HURDLEID::LOWHILL:
		m_tInfo.vSize.x = 87.f;
		m_tInfo.vSize.y = 118.f;
		break;
	case HURDLEID::HIGHHILL:
		m_tInfo.vSize.x = 125.f;
		m_tInfo.vSize.y = 227.f;
		break;
	case HURDLEID::BULLET:
		m_tInfo.vSize.x = 202.f;
		m_tInfo.vSize.y = 117.f;
		break;
	case HURDLEID::CELLING:
		m_tInfo.vSize.x = 165.f;
		m_tInfo.vSize.y = 493.f;
	default:
		break;
	}

	return S_OK;
}

int CFieldHurdle::Update_Object(void)
{
	return OBJ_NOEVENT;
}

void CFieldHurdle::LateUpdate_Object(void)
{
}

void CFieldHurdle::Render_Object(void)
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", byDrawID);

}

void CFieldHurdle::Release_Object(void)
{
	
}
