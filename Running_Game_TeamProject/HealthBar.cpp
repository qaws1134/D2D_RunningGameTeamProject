#include "stdafx.h"
#include "HealthBar.h"
#include "PlayerObserver.h"
#include "Subject.h"

CHealthBar::CHealthBar()
	:m_fHealth(0.f),
	m_pObserver(nullptr)
{

}


CHealthBar::~CHealthBar()
{
	Release_Object();
}

HRESULT CHealthBar::Ready_Object(void)
{
	m_tInfo.vPos = _vec3(170.f, 40.f, 0.f);

	m_tFrame.wstrObjKey = L"HealthBar";

	// 임시 체력값





	// 옵저버 추가
	m_pObserver = CPlayerObserver::Create();
	NULL_CHECK_RETURN(m_pObserver, E_FAIL);
	CSubject::Get_Instance()->Subscribe(m_pObserver);

	



	return S_OK;
}

int CHealthBar::Update_Object(void)
{
	DEAD_CHECK;

	Moving_Logic();

	m_fHealth += 1.f;

	return OBJ_NOEVENT;
}

void CHealthBar::LateUpdate_Object(void)
{
	m_fHealth = static_cast<CPlayerObserver*>(m_pObserver)->Get_PlayerHP();

	FAILED_CHECK_RETURN(Setting_TexInfo(), );
	
}

void CHealthBar::Render_Object(void)
{
	// 체력바 그리기

	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&m_matInfo[MATRIXID::WORLD]);


	RECT rc = { 0, 0, (LONG)(224 - m_fHealth),  39};

	CGraphic_Dev::Get_Instance()->Get_Sprite()->Draw(m_pTexInfo->pTexture,
		&rc,
		&_vec3(m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f),
		nullptr,
		D3DXCOLOR(m_tInfo.vColor.r, m_tInfo.vColor.g, m_tInfo.vColor.b, m_tInfo.vColor.a));
}

void CHealthBar::Release_Object(void)
{
	CSubject::Get_Instance()->UnSubscribe(m_pObserver);
}

void CHealthBar::Moving_Logic(void)
{
	D3DXMatrixIdentity(&m_matInfo[MATRIXID::WORLD]);

	D3DXMatrixScaling(&m_matInfo[MATRIXID::SCALE], m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixTranslation(&m_matInfo[MATRIXID::TRANS], m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_matInfo[MATRIXID::WORLD] = m_matInfo[MATRIXID::SCALE] * m_matInfo[MATRIXID::TRANS];
}

CHealthBar * CHealthBar::Create(void)
{
	CHealthBar*			pInstance = new CHealthBar;

	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);

	return pInstance;	
}
