#include "stdafx.h"
#include "Item.h"
#include "Obj_Manager.h"
#include "Scroll_Manager.h"

CItem::CItem(const ITEMID::ID& eID, const int& iIndex)
	:m_eItemID(eID)
{
	m_tFrame.fStartFrame = (float)iIndex;
}


CItem::~CItem()
{
	Release_Object();
}

HRESULT CItem::Ready_Object(void)
{

	m_tInfo.vSize = _vec3(1.f, 1.f, 0.f);
	m_tFrame.fFrameSpeed = 0.1f;

	m_tFrame.wstrObjKey = L"Item";


	// 각 아이디값마다 이미지 키값인 상태값다르게해서 이미지 불러옴
	switch (m_eItemID)
	{
	case ITEMID::GOLDCOIN_BIG:
	{
		m_tFrame.wstrStateKey = L"GoldCoin_Big";
		m_tFrame.fMaxFrame = 4.f;
	}
		break;
	case ITEMID::GOLDCOIN_SMALL:
	{
		m_tFrame.wstrStateKey = L"GoldCoin_Small";
		m_tFrame.fMaxFrame = 6.f;
	}
		break;
	case ITEMID::SILVERCOIN_BIG:
	{
		m_tFrame.wstrStateKey = L"SilverCoin_Big";
		m_tFrame.fMaxFrame = 4.f;
	}
		break;
	case ITEMID::SILVERCOIN_SMALL:
	{
		m_tFrame.wstrStateKey = L"SilverCoin_Small";
		m_tFrame.fMaxFrame = 4.f;
	}
		break;
	case ITEMID::TRANSCOIN:
	{
		m_tFrame.wstrStateKey = L"TransCoin";
		m_tFrame.fMaxFrame = 4.f;
	}
		break;
	case ITEMID::BIGGEST:
	{
		m_tFrame.wstrStateKey = L"Biggest";
		m_tFrame.fMaxFrame = 4.f;
	}
		break;
	case ITEMID::DASH:
	{
		m_tFrame.wstrStateKey = L"Dash";
		m_tFrame.fMaxFrame = 4.f;
	}
		break;
	case ITEMID::MAGNET:
	{
		m_tFrame.wstrStateKey = L"Magnet";
		m_tFrame.fMaxFrame = 4.f;
	}
		break;
	case ITEMID::ENERGY_BIG:
	{
		m_tFrame.wstrStateKey = L"Energy_Big";
		m_tFrame.fMaxFrame = 4.f;
	}
		break;
	case ITEMID::ENERGY_SMALL:
	{
		m_tFrame.wstrStateKey = L"Energy_Small";
		m_tFrame.fMaxFrame = 4.f;
	}
		break;
	case ITEMID::JELLY_1:
	{
		m_tFrame.wstrStateKey = L"Jelly_1";
		m_tFrame.fMaxFrame = 20.f;
	}
		break;
	case ITEMID::JELLY_2:
	{
		m_tFrame.wstrStateKey = L"Jelly_2";
		m_tFrame.fMaxFrame = 20.f;
	}
		break;
	case ITEMID::JELLY_3:
	{
		m_tFrame.wstrStateKey = L"Jelly_3";
		m_tFrame.fMaxFrame = 10.f;
	}
		break;
	case ITEMID::JELLY_BEAR:
	{
		m_tFrame.wstrStateKey = L"Jelly_Bear";
		m_tFrame.fMaxFrame = 19.f;
	}
		break;
	case ITEMID::TRANSJELLY:
	{
		m_tFrame.wstrStateKey = L"TransJelly";
		m_tFrame.fMaxFrame = 4.f;
	}
		break;
	default:
		break;
	}


	return S_OK;
}

int CItem::Update_Object(void)
{
	DEAD_CHECK;

	Moving_Logic();

	return OBJ_NOEVENT;
}

void CItem::LateUpdate_Object(void)
{

	if ((m_tInfo.vPos.x + (m_tInfo.vSize.x * 0.5f)) < 0)
		m_bDead = true;









	if (m_bIsCollied)
	{
		CObj_Manager::Get_Instance()->Item_Acquired(m_eItemID);
		m_bDead = true;
	}

	if (ITEMID::JELLY_1 == m_eItemID || ITEMID::JELLY_2 == m_eItemID ||
		ITEMID::JELLY_3 == m_eItemID || ITEMID::JELLY_BEAR == m_eItemID)
	{
		FAILED_CHECK_RETURN(Setting_TexInfo(), );
	}
	else
	{
		Move_Frame();
	
		FAILED_CHECK_RETURN(Setting_TexInfo(), );
	}
	 
}

void CItem::Render_Object(void)
{
	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&m_matInfo[MATRIXID::WORLD]);


	CGraphic_Dev::Get_Instance()->Get_Sprite()->Draw(m_pTexInfo->pTexture,
		nullptr,
		&_vec3(m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f),
		nullptr,
		D3DXCOLOR(m_tInfo.vColor.r, m_tInfo.vColor.g, m_tInfo.vColor.b, m_tInfo.vColor.a));
}

void CItem::Release_Object(void)
{
}

CItem * CItem::Create(const ITEMID::ID& eID, const int& iIndex)
{
	CItem*		pInstance = new CItem(eID, iIndex);
	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);

	return pInstance;	
}

void CItem::Moving_Logic(void)
{
	D3DXMatrixIdentity(&m_matInfo[MATRIXID::WORLD]);

	_vec3 vScroll = CScroll_Manager::Get_Instance()->Get_Scroll();


	D3DXMatrixScaling(&m_matInfo[MATRIXID::SCALE], m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixTranslation(&m_matInfo[MATRIXID::TRANS], m_tInfo.vPos.x - vScroll.x, m_tInfo.vPos.y - vScroll.y,  m_tInfo.vPos.z);
	m_matInfo[MATRIXID::WORLD] = m_matInfo[MATRIXID::SCALE] * m_matInfo[MATRIXID::TRANS];
}
