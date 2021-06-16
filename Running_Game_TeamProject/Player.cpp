#include "stdafx.h"
#include "Player.h"
#include "Texture_Manager.h"
#include "KeyMgr.h"
#include "Subject.h"

CPlayer::CPlayer()
	:m_bGiantOn(false), m_fJumpTime(0.f), m_fJumpPower(0.f), m_bJump(false), m_bDoubleJump(false), m_fHPMinus(0.f), m_bDeathCountStart(false), m_bDash(false)
{

}


CPlayer::~CPlayer()
{
	Release_Object();
}

HRESULT CPlayer::Ready_Object(void)
{
	// 체력설정. 나중에 UI에 옵저버패턴으로 넘겨주면 될듯
	m_tInfo.fHP = 224.f;
	m_tInfo.fMaxHP = m_tInfo.fHP;

	m_tInfo.vPos = _vec3(100.f, WINCY >> 1, 0.f);
	//초기값은 러닝
	m_tInfo.fMoveSpeed = 5.f;
	m_tFrame.fStartFrame = 0.f;
	m_tFrame.fMaxFrame = 4.f;
	m_tFrame.wstrObjKey = L"Player";
	m_tFrame.wstrStateKey = L"Run";
	m_tFrame.fFrameSpeed = 0.2f;
	
	// 강화아이템 제한시간 설정
	m_tGiantTime.dwEndTime = 5000;
	m_tDashTime.dwEndTime = 5000;
	m_tMagnetTime.dwEndTime = 5000;

	Setting_TexInfo();
	
	// 상태값이 변화하면 MaxFrame도 변화 ㄱㄱㄱ
	

	// 거대화 제한벡터값, 증가값
	m_vLimitScale = _vec3(2.5f, 2.5f, 0.f);
	m_vScaleIncrease = _vec3(0.02f, 0.02f, 0.f);
	
	m_iCoin = 0;
	m_iJelly = 0;

	// 점프 관련
	m_fJumpPower = 17.f;


	m_fHPMinus = m_tInfo.fMaxHP - m_tInfo.fHP;
	// 옵저버 알림
	CSubject::Get_Instance()->Notify(DATA_MESSAGE::HP, &m_fHPMinus);
	CSubject::Get_Instance()->Notify(DATA_MESSAGE::COIN, &m_iCoin);
	CSubject::Get_Instance()->Notify(DATA_MESSAGE::JELLY, &m_iJelly);


	// 사망후 다음 씬 전환전까지 대기시간
	m_tDeathTime.dwEndTime = 2000;

	return S_OK;
}

int CPlayer::Update_Object(void)
{


	// 체력은 매 프레임마다 1씩 까이도록 임시 설정
	m_tInfo.fHP -= 0.1f;


	// 키 체크
	Key_Input();


	// 아이템 효과 체크
	Item_EffectCheck();


	// 이동함수
	Moving_Logic();

	// 옵저버 갱신
	Notify_Observer();
	
	
	Move_Frame();
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate_Object(void)
{
	// 아이템 효과 시간 체크
	Item_Expired_Check();
	
	LateUpdate_StateCheck();

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

	// 점프중
	if (JUMPING == m_eCurState || DOUBLEJUMPING == m_eCurState)
	{
		if (m_tFrame.fStartFrame >= m_tFrame.fMaxFrame - 1.f)
		{
			// 달리기 아이템 잔여시간이 있을시
			if (m_bDash)
				Switch_State(DASHING);
			else
				Switch_State(RUN);
		}
	}

	// 슬라이딩중
	if (SLIDING == m_eCurState && m_tFrame.fMaxFrame == 3.f)
		Switch_State(RUN);

	// 사망시
	if (DEAD == m_eCurState)
	{
		if (!m_bDeathCountStart && m_tFrame.fStartFrame >= m_tFrame.fMaxFrame - 1.f)
		{
			m_tDeathTime.dwCountTime = GetTickCount();
			m_bDeathCountStart = true;
		}
	}
}

void CPlayer::Release_Object(void)
{
}

void CPlayer::Item_Acquired(const ITEMID::ID & eItemID)
{
	switch (eItemID)
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
		m_iJelly += 120;
	}
	break;
	case ITEMID::SILVERCOIN_BIG:
	{
		m_iCoin += 20;
		m_iJelly += 120;
	}
	break;
	case ITEMID::SILVERCOIN_SMALL:
	{
		m_iCoin += 1;
		m_iJelly += 60;
	}
	break;
	case ITEMID::TRANSCOIN:
	{
		// WINCX 값보다 작은 장애물들 검사해서 코인으로 변환
	}
	break;
	case ITEMID::BIGGEST:
	{
		m_tGiantTime.dwCountTime = GetTickCount();
		m_bGiantOn = true;
	}
	break;
	case ITEMID::DASH:
	{
		m_tDashTime.dwCountTime = GetTickCount();
		Switch_State(DASHING);
		m_bDash = true;
	}
	break;
	case ITEMID::MAGNET:
	{
		// 펫한테 명령줘서 플레이어보다 약간 앞에서 빨아들이도록 명령 함수 ㄱㄱ
	}
	break;
	case ITEMID::ENERGY_BIG:
	{
		// 체력증가
		m_tInfo.fHP += 30.f;
	}
	break;
	case ITEMID::ENERGY_SMALL:
	{
		m_tInfo.fHP += 15.f;
	}
	break;
	case ITEMID::JELLY_1, ITEMID::JELLY_2, ITEMID::JELLY_3:
	{
		m_iJelly += 30;
	}
	break;
	case ITEMID::JELLY_BEAR:
	{
		m_iJelly += 120;
	}
	break;
	case ITEMID::TRANSJELLY:
	{
		// WINCX보다 안에 있는 젤리들을 곰젤리로 바꾸면 될듯
	}
	break;
	default:
		break;
	}
}

void CPlayer::Moving_Logic(void)
{
	// 점프 체크먼저 ㄱㄱ
	Jumping();




	D3DXMatrixIdentity(&m_matInfo[MATRIXID::WORLD]);

	D3DXMatrixScaling(&m_matInfo[MATRIXID::SCALE], m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixTranslation(&m_matInfo[MATRIXID::TRANS], m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_matInfo[MATRIXID::WORLD] = m_matInfo[MATRIXID::SCALE] * m_matInfo[MATRIXID::TRANS];



}

void CPlayer::Key_Input(void)
{
	// 아이템 충돌 테스트용 임시 키인풋값
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_tInfo.vPos.x += 5.f;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_tInfo.vPos.x -= 5.f;
	
	// 점프

	if (!m_bJump && !m_bDoubleJump && CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
		Switch_State(JUMPING);
		m_fJumpTime = 0.f;

	}
	// 더블점프
	if (m_bJump && !m_bDoubleJump && CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = false;
		m_bDoubleJump = true;
		m_fJumpTime = 0.f;
		Switch_State(DOUBLEJUMPING);
	}


	// 슬라이딩
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tFrame.fMaxFrame = 2.f;
		Switch_State(SLIDING);
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_DOWN))
	{
		m_tFrame.fMaxFrame = 3.f;
	}

}

void CPlayer::Item_Expired_Check(void)
{
	//////////////////////// 거대화 아이템 //////////////////////////////////////////////////////////////////////
	if (m_tGiantTime.dwCountTime + m_tGiantTime.dwEndTime < GetTickCount())
	{
		m_bGiantOn = false;
		m_vScaleIncrease = _vec3(0.2f, 0.2f, 0.f);
	}


	// 거대화 크기 제한값
	if (m_bGiantOn && D3DXVec3Length(&m_tInfo.vScale) >= D3DXVec3Length(&m_vLimitScale))
	{
		m_tInfo.vScale = m_vLimitScale;
		m_tInfo.vSize = m_vLimitScale;
	}
	else if (!m_bGiantOn && D3DXVec3Length(&m_tInfo.vScale) <= D3DXVec3Length(&_vec3(1.f, 1.f, 0.f)))
	{
		m_tInfo.vScale = _vec3(1.f, 1.f, 0.f);
		m_tInfo.vSize = _vec3(1.f, 1.f, 0.f);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////// 대쉬 아이템 //////////////////////////////////////////////////////////////////////
	if (DASHING == m_eCurState && m_tDashTime.dwCountTime + m_tDashTime.dwEndTime < GetTickCount())
	{
		m_bDash = false;
		Switch_State(RUN);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////// 마그넷 아이템 /////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 대충 타이머 끝나면 펫한테 뒤로 돌아가라고 명령 하는것보다....

	///////////////////////////////////
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
			m_tInfo.fMoveSpeed = 5.f;
			m_tFrame.fFrameSpeed = 0.2f;
		}
			break;
		case CPlayer::DASHING:
		{
			m_tFrame.wstrStateKey = L"Dash";
			m_tFrame.fMaxFrame = 4;
			m_tInfo.fMoveSpeed = 12.f;
			m_tFrame.fFrameSpeed = 1.f;
		}
			break;
		case CPlayer::JUMPING:
		{
			m_tFrame.wstrStateKey = L"Jump1";
			m_tFrame.fMaxFrame = 2.f;

		}
			break;
		case CPlayer::DOUBLEJUMPING:
		{
			m_tFrame.wstrStateKey = L"Jump2";
			m_tFrame.fMaxFrame = 7.f;
			m_tFrame.fFrameSpeed = 0.2f;
		}
			break;
		case CPlayer::SLIDING:
		{
			m_tFrame.wstrStateKey = L"Sliding";
		}
			break;
		case CPlayer::HIT:
		{
			m_tFrame.wstrStateKey = L"Hit";
			m_tFrame.fMaxFrame = 0.f;

		}
			break;
		case CPlayer::DEAD:
		{
			m_tFrame.wstrStateKey = L"Dead";
			m_tFrame.fMaxFrame = 9.f;

		}
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CPlayer::Jumping(void)
{
	if (m_bJump)
	{
		m_tInfo.vPos.y -= (m_fJumpPower * m_fJumpTime - 0.5f * 9.8f * m_fJumpTime * m_fJumpTime);
		m_fJumpTime += 0.2f;
	}
	if (m_bDoubleJump)
	{
		m_tInfo.vPos.y -= (m_fJumpPower * m_fJumpTime - 0.5f * 9.8f * m_fJumpTime * m_fJumpTime);
		m_fJumpTime += 0.2f;

	}


	

}

void CPlayer::LateUpdate_StateCheck(void)
{
	//////////////////////////// 점프 상태 //////////////////////////////////////////////////////////////////////////////////////



	if (JUMPING == m_eCurState || DOUBLEJUMPING == m_eCurState)
	{
		// 떨어지는중일때는 프레임을 마지막 - 2번째로 고정
 		if (m_tFrame.fStartFrame >= (m_tFrame.fMaxFrame - 2.f) && m_tFrame.fStartFrame <= (m_tFrame.fMaxFrame - 1.f))
			m_tFrame.fStartFrame = m_tFrame.fMaxFrame - 2.f;


		// 착지시 
		if (m_tInfo.vPos.y > (WINCY >> 1))
		{
			m_tInfo.vPos.y = WINCY >> 1;
			m_fJumpTime = 0.f;
			m_tFrame.fStartFrame = m_tFrame.fMaxFrame - 1.f;
			m_bJump = false;
			m_bDoubleJump = false;
			
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////// 장애물 충돌/////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////// 사망 ///////////////////////////////////////////////////////////////////////////////////////////

	if (!m_bDeathCountStart && m_tInfo.fHP <= 0.f)
		Switch_State(DEAD);

	if (m_bDeathCountStart)
		m_tFrame.fStartFrame = m_tFrame.fMaxFrame - 1.f;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void CPlayer::Notify_Observer(void)
{
	// 체력은 최대체력 - 현재체력의 차이값을 넘겨줌
	m_fHPMinus = m_tInfo.fMaxHP - m_tInfo.fHP;

	CSubject::Get_Instance()->Notify(DATA_MESSAGE::HP, &m_fHPMinus);
	CSubject::Get_Instance()->Notify(DATA_MESSAGE::COIN, &m_iCoin);
	CSubject::Get_Instance()->Notify(DATA_MESSAGE::JELLY, &m_iJelly);
}

void CPlayer::Item_EffectCheck(void)
{
	// 거대화시 
	if (m_bGiantOn)
	{
		m_tInfo.vScale += m_vScaleIncrease;
		m_tInfo.vSize += m_vScaleIncrease;
	}
	else if (!m_bGiantOn)
	{
		m_tInfo.vScale -= m_vScaleIncrease;
		m_tInfo.vSize -= m_vScaleIncrease;
	}
}

CPlayer * CPlayer::Create(void)
{
	CPlayer*		pInstance = new CPlayer;
	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);

	return pInstance;
}
