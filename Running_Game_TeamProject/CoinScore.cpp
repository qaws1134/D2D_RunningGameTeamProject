#include "stdafx.h"
#include "CoinScore.h"
#include "Subject.h"
#include "PlayerObserver.h"


CCoinScore::CCoinScore()
	:m_pObserver(nullptr), m_iCoin(0), m_iBufSize(0)
{
}


CCoinScore::~CCoinScore()
{
	Release_Object();
}

HRESULT CCoinScore::Ready_Object(void)
{
	m_tInfo.vPos = _vec3(WINCX - 200.f, 45.f, 0.f);
	m_tFrame.wstrObjKey = L"Item";
	m_tFrame.wstrStateKey = L"SilverCoin_Small";
	m_tFrame.fStartFrame = 0.f;

	// 옵저버 추가
	m_pObserver = CPlayerObserver::Create();
	NULL_CHECK_RETURN(m_pObserver, E_FAIL);
	CSubject::Get_Instance()->Subscribe(m_pObserver);


	return S_OK;
}

int CCoinScore::Update_Object(void)
{
	DEAD_CHECK;

	Moving_Logic();

	return OBJ_NOEVENT;
}

void CCoinScore::LateUpdate_Object(void)
{

	m_iCoin = static_cast<CPlayerObserver*>(m_pObserver)->Get_PlayerCoin();

	wsprintf(m_szBuf, L"%d", m_iCoin);

	m_iBufSize = lstrlen(m_szBuf) + 1;

	FAILED_CHECK_RETURN(Setting_TexInfo(), );

}

void CCoinScore::Render_Object(void)
{
	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&m_matInfo[MATRIXID::WORLD]);


	CGraphic_Dev::Get_Instance()->Get_Sprite()->Draw(m_pTexInfo->pTexture,
		nullptr,
		&_vec3(m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f),
		nullptr,
		D3DXCOLOR(m_tInfo.vColor.r, m_tInfo.vColor.g, m_tInfo.vColor.b, m_tInfo.vColor.a));

	CGraphic_Dev::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Dev::Get_Instance()->Get_Sprite(), m_szBuf, m_iBufSize, nullptr, 0, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

void CCoinScore::Release_Object(void)
{
	CSubject::Get_Instance()->UnSubscribe(m_pObserver);
}

void CCoinScore::Moving_Logic(void)
{
	D3DXMatrixIdentity(&m_matInfo[MATRIXID::WORLD]);

	D3DXMatrixScaling(&m_matInfo[MATRIXID::SCALE], m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixTranslation(&m_matInfo[MATRIXID::TRANS], m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_matInfo[MATRIXID::WORLD] = m_matInfo[MATRIXID::SCALE] * m_matInfo[MATRIXID::TRANS];
}

CCoinScore * CCoinScore::Create(void)
{
	CCoinScore*		pInstance = new CCoinScore;
	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);

	return pInstance;
}
