#include "stdafx.h"
#include "Player.h"
#include "Texture_Manager.h"

CPlayer::CPlayer()
	:m_iCoin(0), m_iJelly(0), m_bInvincible(false), m_bGiantOn(false)
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
	m_tFrame.fMaxFrame = 4.f;
	m_tFrame.wstrObjKey = L"Player";
	m_tFrame.wstrStateKey = L"Run";
	m_tFrame.fFrameSpeed = 0.2f;


	Setting_TexInfo();

	// 상태값이 변화하면 MaxFrame도 변화 ㄱㄱㄱ


	// 거대화 크기제한값
	m_vLimitedScale = _vec3(2.7f, 2.7f, 0.f);



	// 강화 아이템 시간값 설정
	m_tDashTime.dwEndTime		= 5000;
	m_tGiantTime.dwEndTime		= 5000;
	m_tMagnetTime.dwEndTime		= 5000;

	return S_OK;
}

int CPlayer::Update_Object(void)
{
	DEAD_CHECK;

	//if (GetAsyncKeyState(VK_F1) & 0x8000)
	//	Switch_State(DASHING);

	//if (GetAsyncKeyState(VK_F2) & 0x8000)
	//	Switch_State(RUN);

	//if (GetAsyncKeyState(VK_F3) & 0x8000)
	//	Switch_State(DEAD);


	//if (GetAsyncKeyState(VK_F4) & 0x8000)
	//	Switch_State(JUMPING);

	//if (GetAsyncKeyState(VK_F5) & 0x8000)
	//	Switch_State(DOUBLEJUMPING);

	//if (GetAsyncKeyState(VK_F6) & 0x8000)
	//	Switch_State(SLIDING);

	//if (GetAsyncKeyState(VK_F7) & 0x8000)
	//	Switch_State(HIT);


	Key_Input();





	Moving_Logic();



	// 자이언트 테스트
	if (m_bGiantOn && D3DXVec3Length(&m_tInfo.vScale) < D3DXVec3Length(&m_vLimitedScale))
	{
		m_tInfo.vScale += _vec3(0.01f, 0.01f, 0.f);
		m_tInfo.vSize += _vec3(0.01f, 0.01f, 0.f);
	}
	if (!m_bGiantOn && D3DXVec3Length(&m_tInfo.vScale) > D3DXVec3Length(&_vec3(1.f, 1.f, 0.f)))
	{
		m_tInfo.vScale -= _vec3(0.01f, 0.01f, 0.f);
		m_tInfo.vSize -= _vec3(0.01f, 0.01f, 0.f);
	}

	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate_Object(void)
{
	Move_Frame();
	Item_ExpiredTimeCheck();
	FAILED_CHECK_RETURN(Setting_TexInfo(), );
}

void CPlayer::Render_Object(void)
{


	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&m_matInfo[MATRIXID::WORLD]);


	CGraphic_Dev::Get_Instance()->Get_Sprite()->Draw(m_pTexInfo->pTexture,
		nullptr,
		&_vec3(m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f),
		nullptr,
		D3DXCOLOR(m_tInfo.vColor.r, m_tInfo.vColor.g, m_tInfo.vColor.b, m_tInfo.vColor.a));

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

void CPlayer::Item_Acquired(const ITEMID::ID & eID)
{
	switch (eID)
	{
	case ITEMID::GOLDCOIN_BIG:
	{
		m_iCoin += 100;
		m_iJelly = 240;
	}
	break;
	case ITEMID::GOLDCOIN_SMALL:
	{
		m_iCoin += 10;
		m_iJelly = 120;
	}
	break;
	case ITEMID::SILVERCOIN_BIG:
	{
		m_iCoin += 20;
		m_iJelly = 120;
	}
	break;
	case ITEMID::SILVERCOIN_SMALL:
	{
		m_iCoin += 1;
		m_iJelly = 60;
	}
	break;
	case ITEMID::TRANSCOIN:
	{
		// WINCX 보다 작은 위치에 있는 장애물들 코인으로 바꾸는걸로
	}
	break;
	case ITEMID::BIGGEST:
	{
		m_bGiantOn = true;
		m_tGiantTime.dwCountTime = GetTickCount();
	}
	break;
	case ITEMID::DASH:
	{
	}
	break;
	case ITEMID::MAGNET:
	{
	}
	break;
	case ITEMID::ENERGY_BIG:
	{
	}
	break;
	case ITEMID::ENERGY_SMALL:
	{
	}
	break;
	case ITEMID::JELLY_1:
		m_iJelly += 30;
		break;
	case ITEMID::JELLY_2:
		m_iJelly += 30;
		break;
	case ITEMID::JELLY_3:
		m_iJelly += 30;
		break;
	case ITEMID::JELLY_BEAR:
		m_iJelly = 120;
		break;
	case ITEMID::TRANSJELLY:
	{
		// WINCX 보다 작은 x값에 있는 젤리들 전부 곰젤리로 바꿈
	}
	default:
		break;
	}
}

void CPlayer::Key_Input(void)
{
	// 아이템 충돌 테스트용 움직임
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_tInfo.vPos.x += 5.f;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_tInfo.vPos.x -= 5.f;
}

void CPlayer::Item_ExpiredTimeCheck(void)
{
	// 대쉬
	if (m_tDashTime.dwCountTime + m_tDashTime.dwEndTime < GetTickCount())
	{

	}
	// 거대화
	if (m_tGiantTime.dwCountTime + m_tGiantTime.dwEndTime < GetTickCount())
	{
		m_bGiantOn = false;
	}
	// 마그넷
	if (m_tMagnetTime.dwCountTime + m_tMagnetTime.dwEndTime < GetTickCount())
	{

	}
}

void CPlayer::Switch_State(const PLAYER_STATE & eState)
{
	m_eCurState = eState;

	if (m_ePreState != m_eCurState)
	{
		m_tFrame.fStartFrame = 0.f;

		switch (m_eCurState)
		{
		case CPlayer::RUN:
		{
			m_tFrame.wstrStateKey = L"Run";
			m_tFrame.fMaxFrame = 4;

		}
		break;
		case CPlayer::DASHING:
		{
			m_tFrame.wstrStateKey = L"Dash";
			m_tFrame.fMaxFrame = 4;

		}
		break;
		case CPlayer::JUMPING:
		{
			m_tFrame.wstrStateKey = L"Jump1";
			m_tFrame.fMaxFrame = 2;

		}
		break;
		case CPlayer::DOUBLEJUMPING:
		{
			m_tFrame.wstrStateKey = L"Jump2";
			m_tFrame.fMaxFrame = 7;

		}
		break;
		case CPlayer::SLIDING:
		{
			m_tFrame.wstrStateKey = L"Sliding";
			m_tFrame.fMaxFrame = 3;

		}
		break;
		case CPlayer::HIT:
		{
			m_tFrame.wstrStateKey = L"Hit";
			m_tFrame.fMaxFrame = 0;

		}
		break;
		case CPlayer::DEAD:
		{
			m_tFrame.wstrStateKey = L"Dead";
			m_tFrame.fMaxFrame = 9;

		}
		break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}

CPlayer * CPlayer::Create(void)
{
	CPlayer*		pInstance = new CPlayer;
	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);

	return pInstance;
}
