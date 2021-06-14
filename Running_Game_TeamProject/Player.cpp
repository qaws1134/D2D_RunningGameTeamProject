#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_Object(void)
{
	return E_NOTIMPL;
}

int CPlayer::Update_Object(void)
{
	return 0;
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

CPlayer * CPlayer::Create(void)
{
	CPlayer*		pInstance = new CPlayer;
	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);

	return pInstance;
}
