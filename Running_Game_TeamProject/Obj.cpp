#include "stdafx.h"
#include "Obj.h"
#include "Texture_Manager.h"


CObj::CObj()
	:m_bDead(false), m_bIsCollied(false), m_pTexInfo(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));

	for (int i = 0; i < MATRIXID::END; ++i)
		ZeroMemory(&m_matInfo[i], sizeof(_mat));

	m_tInfo.vColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
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

HRESULT CObj::Setting_TexInfo(void)
 {
	m_pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(m_tFrame.wstrObjKey, m_tFrame.wstrStateKey, (int)m_tFrame.fStartFrame);

	NULL_CHECK_RETURN(m_pTexInfo, E_FAIL);

	m_tInfo.vSize = _vec3((float)m_pTexInfo->tImageInfo.Width, (float)m_pTexInfo->tImageInfo.Height, 0.f);

	return S_OK;
}

void CObj::Move_Frame(void)
{
	// 프레임 증가
	m_tFrame.fStartFrame += m_tFrame.fFrameSpeed;

	if (m_tFrame.fStartFrame > m_tFrame.fMaxFrame)
		m_tFrame.fStartFrame = 0.f;
}

void CObj::Ready_Rectangle(void)
{
	// 좌상
	m_tInfo.vPoint[0] = _vec3(-m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f);
	// 우상
	m_tInfo.vPoint[1] = _vec3(m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f);
	// 우하
	m_tInfo.vPoint[2] = _vec3(m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f);
	// 좌하
	m_tInfo.vPoint[3] = _vec3(-m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f);
}

