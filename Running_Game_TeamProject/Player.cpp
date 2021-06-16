#include "stdafx.h"
#include "Player.h"
#include "Texture_Manager.h"
#include "KeyMgr.h"
#include "Subject.h"
#include "LineMgr.h"
CPlayer::CPlayer()
	:m_bGiantOn(false), m_fJumpTime(0.f), m_fJumpPower(0.f)
	, m_bJump(false), m_bDoubleJump(false), m_fHPMinus(0.f)
	, m_bDeathCountStart(false), m_bDash(false), m_bSuper(false)
	, m_iSuperTime(0), m_dwSuperTime(GetTickCount()), m_fJumpY(0.f), m_bDown(false),m_iDownTime(0),m_dwDownTime(GetTickCount())
	, m_fIncrese(0.f), m_bHit(false)

{

}


CPlayer::~CPlayer()
{
	Release_Object();
}

HRESULT CPlayer::Ready_Object(void)
{
	// ü�¼���. ���߿� UI�� �������������� �Ѱ��ָ� �ɵ�
	m_tInfo.fHP = 224.f;
	m_tInfo.fMaxHP = m_tInfo.fHP;

	m_tInfo.vPos = _vec3(100.f, WINCY-(WINCY >> 2), 0.f);
	//�ʱⰪ�� ����
	m_tInfo.fMoveSpeed = 5.f;
	m_tFrame.fStartFrame = 0.f;
	m_tFrame.fMaxFrame = 4.f;
	m_tFrame.wstrObjKey = L"Player";
	m_tFrame.wstrStateKey = L"Run";
	m_tFrame.fFrameSpeed = 0.2f;
	// ��ȭ������ ���ѽð� ����
	m_tGiantTime.dwEndTime = 5000;
	m_tDashTime.dwEndTime = 5000;
	m_tMagnetTime.dwEndTime = 5000;

	Setting_TexInfo();
	
	// ���°��� ��ȭ�ϸ� MaxFrame�� ��ȭ ������


	// �Ŵ�ȭ ���Ѻ��Ͱ�, ������
	m_vLimitScale = _vec3(2.5f, 2.5f, 0.f);
	m_vScaleIncrease = _vec3(0.02f, 0.02f, 0.f);
	
	m_iCoin = 0;
	m_iJelly = 0;

	//����
	m_iSuperTime = 2000;


	// ���� ����
	m_fJumpPower = 60.f;
	m_iDownTime = 1000;

	m_fHPMinus = m_tInfo.fMaxHP - m_tInfo.fHP;
	// ������ �˸�
	CSubject::Get_Instance()->Notify(DATA_MESSAGE::HP, &m_fHPMinus);
	CSubject::Get_Instance()->Notify(DATA_MESSAGE::COIN, &m_iCoin);
	CSubject::Get_Instance()->Notify(DATA_MESSAGE::JELLY, &m_iJelly);


	m_tHitTime.dwEndTime = 500;


	m_tAlphaTime.dwEndTime = 200;


	// ����� ���� �� ��ȯ������ ���ð�
	m_tDeathTime.dwEndTime = 2000;

	return S_OK;
}

int CPlayer::Update_Object(void)
{


	// ü���� �� �����Ӹ��� 1�� ���̵��� �ӽ� ����
	//m_tInfo.fHP -= 0.1f;

	SuperTime();
	// Ű üũ
	Key_Input();


	// ������ ȿ�� üũ
	Item_EffectCheck();


	// �̵��Լ�
	Moving_Logic();

	// ������ ����
	Notify_Observer();
	
	if(m_eCurState != HIT) 
		Move_Frame();

	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate_Object(void)
{
	// ������ ȿ�� �ð� üũ
	Item_Expired_Check();
	
	LateUpdate_StateCheck();

	if (m_eCurState == HIT)
		m_tFrame.fStartFrame = 0.f;

	FAILED_CHECK_RETURN(Setting_TexInfo(), );
}

void CPlayer::Render_Object(void)
{


	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&m_matInfo[MATRIXID::WORLD]);


	CGraphic_Dev::Get_Instance()->Get_Sprite()->Draw(m_pTexInfo->pTexture, 
														nullptr, 
														&_vec3(m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f + m_fIncrese, 0.f),
														nullptr, 
														D3DXCOLOR(m_tInfo.vColor.r, m_tInfo.vColor.g, m_tInfo.vColor.b, m_tInfo.vColor.a));

	// ������
	if (JUMPING == m_eCurState || DOUBLEJUMPING == m_eCurState)
	{
		if (m_tFrame.fStartFrame >= m_tFrame.fMaxFrame - 1.f)
		{
			// �޸��� ������ �ܿ��ð��� ������
			if (m_bDash)
				Switch_State(DASHING);
			else
				Switch_State(RUN);
		}
	}

	// �����̵���
	if (SLIDING == m_eCurState && m_tFrame.fMaxFrame == 3.f)
		Switch_State(RUN);

	// �����
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
		m_iJelly += 240;
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
		// WINCX ������ ���� ��ֹ��� �˻��ؼ� �������� ��ȯ
	}
	break;
	case ITEMID::BIGGEST:
	{
		m_tGiantTime.dwCountTime = GetTickCount();
		m_bSuper = true;
		m_bGiantOn = true;
		m_bSuper = true;
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
		// ������ �����༭ �÷��̾�� �ణ �տ��� ���Ƶ��̵��� ���� �Լ� ����
	}
	break;
	case ITEMID::ENERGY_BIG:
	{
		// ü������
		m_tInfo.fHP += 30.f;
		if (m_tInfo.fMaxHP <= m_tInfo.fHP)
			m_tInfo.fHP = m_tInfo.fMaxHP;
	}
	break;
	case ITEMID::ENERGY_SMALL:
	{
		m_tInfo.fHP += 15.f;
		if (m_tInfo.fMaxHP <= m_tInfo.fHP)
			m_tInfo.fHP = m_tInfo.fMaxHP;
	}
	break;
	case ITEMID::JELLY_1:
	{
		m_iJelly += 30;
	}
	break;
	case ITEMID::JELLY_2:
	{
		m_iJelly += 30;
	}
	break;

	case ITEMID::JELLY_3:
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
		// WINCX���� �ȿ� �ִ� �������� �������� �ٲٸ� �ɵ�
	}
	break;
	default:
		break;
	}
}

void CPlayer::SuperTime()
{
	if (m_bSuper)
	{
		if (m_dwSuperTime + m_iSuperTime < GetTickCount())
		{
			m_bSuper = false;
			m_dwSuperTime = GetTickCount();
			m_tInfo.vColor.a = 1.f;
		}
	}
}

void CPlayer::Moving_Logic(void)
{
	// ���� üũ���� ����
	Jumping();









	D3DXMatrixIdentity(&m_matInfo[MATRIXID::WORLD]);

	D3DXMatrixScaling(&m_matInfo[MATRIXID::SCALE], m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixTranslation(&m_matInfo[MATRIXID::TRANS], m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_matInfo[MATRIXID::WORLD] = m_matInfo[MATRIXID::SCALE] * m_matInfo[MATRIXID::TRANS];

}

void CPlayer::Key_Input(void)
{
	// ������ �浹 �׽�Ʈ�� �ӽ� Ű��ǲ��
	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//	m_tInfo.vPos.x += 5.f;
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//	m_tInfo.vPos.x -= 5.f;
	
	// ����

	if (!m_bJump && !m_bDoubleJump && CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (!m_bJump)
			m_fJumpY = m_tInfo.vPos.y;
		m_bJump = true;
		Switch_State(JUMPING);
		m_fJumpTime = 0.f;

	}
	// ��������
	if (m_bJump && !m_bDoubleJump && CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (!m_bDoubleJump)
			m_fJumpY = m_tInfo.vPos.y;
		m_bJump = false;
		m_bDoubleJump = true;

		m_fJumpTime = 0.f;
		Switch_State(DOUBLEJUMPING);
	}


	// �����̵�
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
	//////////////////////// �Ŵ�ȭ ������ //////////////////////////////////////////////////////////////////////
	if (m_tGiantTime.dwCountTime + m_tGiantTime.dwEndTime < GetTickCount())
	{
		m_bGiantOn = false;
		m_vScaleIncrease = _vec3(0.2f, 0.2f, 0.f);
	}

	// �Ŵ�ȭ ũ�� ���Ѱ�
	if (m_bGiantOn && D3DXVec3Length(&m_tInfo.vScale) >= D3DXVec3Length(&m_vLimitScale))
	{
		m_tInfo.vScale = m_vLimitScale;
		m_fIncrese = 45.f;
		//m_tInfo.vSize *= 2.5f;
	}
	else if (!m_bGiantOn && D3DXVec3Length(&m_tInfo.vScale) <= D3DXVec3Length(&_vec3(1.f, 1.f, 0.f)))
	{
		m_tInfo.vScale = _vec3(1.f, 1.f, 0.f);
		m_fIncrese = 0.f;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////// �뽬 ������ //////////////////////////////////////////////////////////////////////
	if (DASHING == m_eCurState && m_tDashTime.dwCountTime + m_tDashTime.dwEndTime < GetTickCount())
	{
		m_bDash = false;
		Switch_State(RUN);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////// ���׳� ������ /////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ���� Ÿ�̸� ������ ������ �ڷ� ���ư���� ���� �ϴ°ͺ���....

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
	float fY = 0.f;
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.vPos.x, &fY);
	if (m_bJump)
	{
		m_tInfo.vPos.y = m_fJumpY-(m_fJumpPower * m_fJumpTime - 0.5f * 12.8f * m_fJumpTime * m_fJumpTime);
		m_fJumpTime += 0.2f;
		if (bLineCol&& fY < m_tInfo.vPos.y)
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tFrame.fStartFrame = m_tFrame.fMaxFrame - 1.f;
			m_bDoubleJump = false;
		}
	}
	else if (m_bDoubleJump)
	{
		m_tInfo.vPos.y = m_fJumpY-(m_fJumpPower * m_fJumpTime - 0.5f * 12.8f * m_fJumpTime * m_fJumpTime);
		m_fJumpTime += 0.2f;
		if (bLineCol&& fY < m_tInfo.vPos.y)
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tFrame.fStartFrame = m_tFrame.fMaxFrame - 1.f;
			m_bDoubleJump = false;
		}
	}
	else if(bLineCol)		//���� üũ�ؼ� y �� �ش�  �ٴ��� ��ģ �� ������ ������ m_bdown true�� �༭�ٴ��� ���ƴٰ� ����
	{
		if (m_bDown)
		{
			m_tInfo.vPos.y -= (1 * m_fJumpTime - 0.5f * 9.8f * m_fJumpTime * m_fJumpTime);
			m_fJumpTime += 0.1f;
			if (m_dwDownTime + m_iDownTime < GetTickCount())
			{
				m_bDown = false;
				m_bSuper = true;
				m_tInfo.fHP -= 2.f;
				m_dwDownTime=GetTickCount();
			}
		}
		else
		{
			m_fJumpTime = 0.f;
			m_tInfo.vPos.y = fY;
			 
		}
		
	}
	else if (!bLineCol)
	{
		if (!m_bDown)
		{
			m_bDown = true;
			m_dwDownTime = GetTickCount();
		}
		m_tInfo.vPos.y -=  (1 * m_fJumpTime - 0.5f * 9.8f * m_fJumpTime * m_fJumpTime);
		m_fJumpTime += 0.1f;
		if (bLineCol&&fY < m_tInfo.vPos.y)	//����	//���� �浹���̰� pos y ���� �÷��̾�� ������ 
		{
			m_fJumpTime = 0.f;
			m_bJump = false;
			m_tFrame.fStartFrame = m_tFrame.fMaxFrame - 2.f;
			m_bDoubleJump = false;
		}
	}



	

}

void CPlayer::LateUpdate_StateCheck(void)
{
	//////////////////////////// ���� ���� //////////////////////////////////////////////////////////////////////////////////////



	if (JUMPING == m_eCurState || DOUBLEJUMPING == m_eCurState)
	{
		if (m_bJump || m_bDoubleJump)
		{
			// �����������϶��� �������� ������ - 2��°�� ����
			if (m_tFrame.fStartFrame >= (m_tFrame.fMaxFrame - 2.f) && m_tFrame.fStartFrame <= (m_tFrame.fMaxFrame - 1.f))
				m_tFrame.fStartFrame = m_tFrame.fMaxFrame - 2.f;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////// ��ֹ� �浹/////////////////////////////////////////////////////////////////////////////////////


	if (m_bHit && m_tHitTime.dwCountTime + m_tHitTime.dwEndTime < GetTickCount())
	{
		m_bHit = false;
		Switch_State(RUN);
	}


	// ���İ� ����
	if (m_bSuper)
	{
		if (m_tAlphaTime.dwCountTime + m_tAlphaTime.dwEndTime < GetTickCount())
			m_tInfo.vColor.a *= -1.f;
	}




	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////// ��� ///////////////////////////////////////////////////////////////////////////////////////////

	if (!m_bDeathCountStart && m_tInfo.fHP <= 0.f)
		Switch_State(DEAD);

	if (m_bDeathCountStart)
		m_tFrame.fStartFrame = m_tFrame.fMaxFrame - 1.f;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void CPlayer::Notify_Observer(void)
{
	// ü���� �ִ�ü�� - ����ü���� ���̰��� �Ѱ���
	m_fHPMinus = m_tInfo.fMaxHP - m_tInfo.fHP;

	CSubject::Get_Instance()->Notify(DATA_MESSAGE::HP, &m_fHPMinus);
	CSubject::Get_Instance()->Notify(DATA_MESSAGE::COIN, &m_iCoin);
	CSubject::Get_Instance()->Notify(DATA_MESSAGE::JELLY, &m_iJelly);
}

void CPlayer::Item_EffectCheck(void)
{
	// �Ŵ�ȭ�� 
	if (m_bGiantOn)
	{
		m_bSuper = true;
		m_dwSuperTime= GetTickCount();
		m_tInfo.vScale += m_vScaleIncrease;
		m_fIncrese += 0.7f;
		//m_tInfo.vSize += m_vScaleIncrease;
	}
	else if (!m_bGiantOn)
	{
		m_fIncrese -= 7.f;
		m_tInfo.vScale -= m_vScaleIncrease;
		//m_tInfo.vSize -= m_vScaleIncrease;
	}
}

void	CPlayer::Set_Hp()
{
	if (!m_bSuper)m_tInfo.fHP -= 20.f;


	Switch_State(HIT);

	m_tHitTime.dwCountTime = GetTickCount();
}



void	CPlayer::Set_Super()
{
	m_bSuper = true; 
	m_bHit = true;
	m_dwSuperTime = GetTickCount();


	m_tAlphaTime.dwCountTime = GetTickCount();
}



CPlayer * CPlayer::Create(void)
{
	CPlayer*		pInstance = new CPlayer;
	if (FAILED(pInstance->Ready_Object()))
		Safe_Delete(pInstance);

	return pInstance;
}
