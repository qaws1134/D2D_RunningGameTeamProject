#include "stdafx.h"
#include "HealthIcon.h"


CHealthIcon::CHealthIcon()
{
}


CHealthIcon::~CHealthIcon()
{
	Release_Object();
}

HRESULT CHealthIcon::Ready_Object(void)
{
	m_tInfo.vPos = _vec3(26.f, 40.f, 0.f);
	m_tFrame.wstrObjKey = L"HealthIcon";



	return S_OK;
}

int CHealthIcon::Update_Object(void)
{
	DEAD_CHECK;

	Moving_Logic();

	return OBJ_NOEVENT;
}

void CHealthIcon::LateUpdate_Object(void)
{
	FAILED_CHECK_RETURN(Setting_TexInfo(), );

}

void CHealthIcon::Render_Object(void)
{
	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&m_matInfo[MATRIXID::WORLD]);


	CGraphic_Dev::Get_Instance()->Get_Sprite()->Draw(m_pTexInfo->pTexture,
		nullptr,
		&_vec3(m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f),
		nullptr,
		D3DXCOLOR(m_tInfo.vColor.r, m_tInfo.vColor.g, m_tInfo.vColor.b, m_tInfo.vColor.a));
}

void CHealthIcon::Release_Object(void)
{
}



void CHealthIcon::Moving_Logic(void)
{
	D3DXMatrixIdentity(&m_matInfo[MATRIXID::WORLD]);

	D3DXMatrixScaling(&m_matInfo[MATRIXID::SCALE], m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixTranslation(&m_matInfo[MATRIXID::TRANS], m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_matInfo[MATRIXID::WORLD] = m_matInfo[MATRIXID::SCALE] * m_matInfo[MATRIXID::TRANS];

}

CHealthIcon * CHealthIcon::Create()
{
	CHealthIcon*		pInstance = new CHealthIcon;

	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);

	return pInstance;
}
