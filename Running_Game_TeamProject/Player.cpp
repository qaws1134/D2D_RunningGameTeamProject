#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release_Object();
}

HRESULT CPlayer::Ready_Object(void)
{
	m_tInfo.vPos = _vec3(WINCX >> 1, WINCY >> 1, 0.f);
	m_tInfo.vSize = _vec3(50.f, 50.f, 0.f);

	Ready_Rectangle();
	return S_OK;
}

int CPlayer::Update_Object(void)
{
	DEAD_CHECK;


	Moving_Logic();


	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate_Object(void)
{
}

void CPlayer::Render_Object(void)
{
}

void CPlayer::Release_Object(void)
{
}

void CPlayer::Moving_Logic(void)
{
	_mat matScale, matTrans, matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	matWorld = matScale * matTrans;




}

CPlayer * CPlayer::Create(void)
{
	CPlayer*		pInstance = new CPlayer;
	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);

	return pInstance;
}
