#include "stdafx.h"
#include "FieldHurdle.h"
#include "Texture_Manager.h"

CFieldHurdle::CFieldHurdle(): byDrawID(0),byOption(0)
{
}


CFieldHurdle::~CFieldHurdle()
{
}

CFieldHurdle * CFieldHurdle::Create(_vec3 _vPos, HURDLEID::ID _eID)
{
	CFieldHurdle*	pInstance = new CFieldHurdle;
	pInstance->Set_Pos(_vPos);
	pInstance->Set_ID(_eID);
	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);

	return pInstance;
}

HRESULT CFieldHurdle::Ready_Object(void)
{

	m_tInfo.vScale = _vec3(1.f, 1.f, 0.f);

	m_tFrame.wstrObjKey = L"1-1";

	switch (m_eID)
	{
	case HURDLEID::FLOOR:
		m_tInfo.vSize.x = 124.f;
		m_tInfo.vSize.y = 140.f;
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.fMaxFrame = 0.f;
		m_tFrame.wstrStateKey = L"Floor";
		m_tFrame.fFrameSpeed = 0.f;
		break;
	case HURDLEID::FLOOR2F:
		m_tInfo.vSize.x = 129.f;
		m_tInfo.vSize.y = 52.f;
		m_tFrame.fStartFrame = 1.f;
		m_tFrame.fMaxFrame = 1.f;
		m_tFrame.wstrStateKey = L"Floor";
		m_tFrame.fFrameSpeed = 0.f;
		break;
	case HURDLEID::LOWHILL:
		m_tInfo.vSize.x = 87.f;
		m_tInfo.vSize.y = 118.f;
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.fMaxFrame = 0.f;
		m_tFrame.wstrStateKey = L"LowHill";
		m_tFrame.fFrameSpeed = 0.f;
		break;
	case HURDLEID::HIGHHILL:
		m_tInfo.vSize.x = 125.f;
		m_tInfo.vSize.y = 227.f;
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.fMaxFrame = 0.f;
		m_tFrame.wstrStateKey = L"HighHill";
		m_tFrame.fFrameSpeed = 0.f;
		break;
	case HURDLEID::BULLET:
		m_tInfo.vSize.x = 202.f;
		m_tInfo.vSize.y = 117.f;
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.fMaxFrame = 3.f;
		m_tFrame.wstrStateKey = L"Bullet";
		m_tFrame.fFrameSpeed = 0.2f;
		break;
	case HURDLEID::BULLET_CRASH:
		m_tInfo.vSize.x = 202.f;
		m_tInfo.vSize.y = 117.f;
		m_tFrame.fStartFrame = 3.f;
		m_tFrame.fMaxFrame = 8.f;
		m_tFrame.wstrStateKey = L"Bullet";
		m_tFrame.fFrameSpeed = 0.2f;
		break;
	case HURDLEID::CELLING:
		m_tInfo.vSize.x = 165.f;
		m_tInfo.vSize.y = 493.f;
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.fMaxFrame = 0.f;
		m_tFrame.wstrStateKey = L"Celling";
		m_tFrame.fFrameSpeed = 0.f;
	default:
		break;
	}
	Setting_TexInfo();

	return S_OK;
}

int CFieldHurdle::Update_Object(void)
{
	Moving_Logic();
	return OBJ_NOEVENT;
}

void CFieldHurdle::LateUpdate_Object(void)
{
	Move_Frame();
}

void CFieldHurdle::Render_Object(void)
{
	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&m_matInfo[MATRIXID::WORLD]);


	CGraphic_Dev::Get_Instance()
		->Get_Sprite()
		->Draw(m_pTexInfo->pTexture
			,nullptr
			,&_vec3(m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f)
			,nullptr
			,D3DXCOLOR(m_tInfo.vColor.r, m_tInfo.vColor.g, m_tInfo.vColor.b, m_tInfo.vColor.a));

}

void CFieldHurdle::Release_Object(void)
{
	
}

void CFieldHurdle::Move_Frame()
{

	m_tFrame.fStartFrame += m_tFrame.fFrameSpeed;

	if (m_eID == HURDLEID::BULLET_CRASH)
	{
		if (m_tFrame.fStartFrame > m_tFrame.fMaxFrame)
			m_tFrame.fStartFrame = m_tFrame.fMaxFrame - 1;
		//프레임 종료
	}
	else
	{
		if (m_tFrame.fStartFrame > m_tFrame.fMaxFrame)
			m_tFrame.fStartFrame = 0.f;
	}
}

void CFieldHurdle::Moving_Logic(void)
{
	D3DXMatrixIdentity(&m_matInfo[MATRIXID::WORLD]);

	D3DXMatrixScaling(&m_matInfo[MATRIXID::SCALE], m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixTranslation(&m_matInfo[MATRIXID::TRANS], m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_matInfo[MATRIXID::WORLD] = m_matInfo[MATRIXID::SCALE] * m_matInfo[MATRIXID::TRANS];
}
