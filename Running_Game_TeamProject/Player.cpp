#include "stdafx.h"
#include "Player.h"
#include "Texture_Manager.h"

CPlayer::CPlayer()
{
	// 주석 테스트
}


CPlayer::~CPlayer()
{
	Release_Object();
}

HRESULT CPlayer::Ready_Object(void)
{

	m_tInfo.vPos = _vec3(WINCX >> 1, WINCY >> 1, 0.f);
	m_tInfo.vScale = _vec3(1.f, 1.f, 0.f);
	//초기값은 러닝

	m_tFrame.fStartFrame = 0.f;
	m_tFrame.wstrObjKey = L"Player";
	m_tFrame.wstrStateKey = L"Run";
	m_tFrame.fFrameSpeed = 0.2f;
	

	Setting_TexInfo();
	
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
	FAILED_CHECK_RETURN(Setting_TexInfo(), );
}

void CPlayer::Render_Object(void)
{


	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&m_matInfo[MATRIXID::WORLD]);


	//CGraphic_Dev::Get_Instance()->Get_Sprite()->Draw(m_pTexInfo->pTexture, 
	//													nullptr, 
	//													&_vec3(m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f), 
	//													nullptr, 
	//													D3DXCOLOR(m_tInfo.vColor.r, m_tInfo.vColor.g, m_tInfo.vColor.b, m_tInfo.vColor.a));



}

void CPlayer::Release_Object(void)
{

}

void CPlayer::Moving_Logic(void)
{
	D3DXMatrixIdentity(&m_matInfo[MATRIXID::WORLD]);

	D3DXMatrixScaling(&m_matInfo[MATRIXID::SCALE], m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixTranslation(&m_matInfo[MATRIXID::TRANS], m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_matInfo[MATRIXID::WORLD] = m_matInfo[MATRIXID::SCALE] * m_matInfo[MATRIXID::TRANS];


}

CPlayer * CPlayer::Create(void)
{
	CPlayer*		pInstance = new CPlayer;
	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);
	return pInstance;
}
