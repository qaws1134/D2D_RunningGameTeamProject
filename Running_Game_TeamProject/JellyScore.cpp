#include "stdafx.h"
#include "JellyScore.h"
#include "Subject.h"
#include "PlayerObserver.h"

CJellyScore::CJellyScore()
	:m_pObserver(nullptr), m_iJelly(0), m_iBufSize(0)
{
}


CJellyScore::~CJellyScore()
{
	Release_Object();
}

HRESULT CJellyScore::Ready_Object(void)
{

	m_tInfo.vPos = _vec3((WINCX >> 1) - 50.f, 40.f, 0.f);


	m_tFrame.wstrObjKey = L"Item";
	m_tFrame.wstrStateKey = L"Jelly_1";
	m_tFrame.fStartFrame = 0.f;

	// 옵저버 추가
	m_pObserver = CPlayerObserver::Create();
	NULL_CHECK_RETURN(m_pObserver, E_FAIL);
	CSubject::Get_Instance()->Subscribe(m_pObserver);

	return S_OK;
}

int CJellyScore::Update_Object(void)
{
	DEAD_CHECK;

	Moving_Logic();
	return OBJ_NOEVENT;
}

void CJellyScore::LateUpdate_Object(void)
{

	m_iJelly = static_cast<CPlayerObserver*>(m_pObserver)->Get_PlayerJelly();

	wsprintf(m_szBuf, L"%d", m_iJelly);

	FAILED_CHECK_RETURN(Setting_TexInfo(), );

}

void CJellyScore::Render_Object(void)
{

	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&m_matInfo[MATRIXID::WORLD]);


	CGraphic_Dev::Get_Instance()->Get_Sprite()->Draw(m_pTexInfo->pTexture,
		nullptr,
		&_vec3(m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f),
		nullptr,
		D3DXCOLOR(m_tInfo.vColor.r, m_tInfo.vColor.g, m_tInfo.vColor.b, m_tInfo.vColor.a));
	

	m_iBufSize = lstrlen(m_szBuf) + 1;

	// 글자출력
	CGraphic_Dev::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Dev::Get_Instance()->Get_Sprite(), m_szBuf, m_iBufSize, nullptr, DT_CENTER, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

}

void CJellyScore::Release_Object(void)
{
	CSubject::Get_Instance()->UnSubscribe(m_pObserver);
}

void CJellyScore::Moving_Logic(void)
{
	D3DXMatrixIdentity(&m_matInfo[MATRIXID::WORLD]);

	D3DXMatrixScaling(&m_matInfo[MATRIXID::SCALE], m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixTranslation(&m_matInfo[MATRIXID::TRANS], m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_matInfo[MATRIXID::WORLD] = m_matInfo[MATRIXID::SCALE] * m_matInfo[MATRIXID::TRANS];
}

CJellyScore * CJellyScore::Create(void)
{
	CJellyScore*		pInstance = new CJellyScore;
	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);

	return pInstance;
}
