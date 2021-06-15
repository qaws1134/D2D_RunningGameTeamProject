#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release_Object();
}

HRESULT CPlayer::Ready_Object(void)
{
	m_tInfo.vPos = _vec3(WINCX >> 1, WINCY >> 1, 0.f);
<<<<<<< Updated upstream
	m_tInfo.vSize = _vec3(50.f, 50.f, 0.f);

	Ready_Rectangle();
=======
	m_tInfo.vScale = _vec3(1.f, 1.f, 0.f);
	//초기값은 러닝

	m_tFrame.fStartFrame = 0.f;
	m_tFrame.fMaxFrame = 4.f;
	m_tFrame.wstrObjKey = L"Player";
	m_tFrame.wstrStateKey = L"Run";
	m_tFrame.fFrameSpeed = 0.2f;
	

	Setting_TexInfo();
	
	// 상태값이 변화하면 MaxFrame도 변화 ㄱㄱㄱ
	

>>>>>>> Stashed changes
	return S_OK;
}

int CPlayer::Update_Object(void)
{
	DEAD_CHECK;

	if (GetAsyncKeyState(VK_F1) & 0x8000)
		Switch_State(DASHING);

	if (GetAsyncKeyState(VK_F2) & 0x8000)
		Switch_State(RUN);

	if (GetAsyncKeyState(VK_F3) & 0x8000)
		Switch_State(DEAD);


	if (GetAsyncKeyState(VK_F4) & 0x8000)
		Switch_State(JUMPING);

	if (GetAsyncKeyState(VK_F5) & 0x8000)
		Switch_State(DOUBLEJUMPING);

	if (GetAsyncKeyState(VK_F6) & 0x8000)
		Switch_State(SLIDING);

	if (GetAsyncKeyState(VK_F7) & 0x8000)
		Switch_State(HIT);







	Moving_Logic();


	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate_Object(void)
{
<<<<<<< Updated upstream
=======
	Move_Frame();

	FAILED_CHECK_RETURN(Setting_TexInfo(), );
>>>>>>> Stashed changes
}

void CPlayer::Render_Object(void)
{
}

void CPlayer::Release_Object(void)
{
}

void CPlayer::Moving_Logic(void)
{
	_mat matScale, matTrans, matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	matWorld = matScale * matTrans;




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
			m_tInfo.vScale = _vec3(0.5f, 0.5f, 0.f);

		}
			break;
		case CPlayer::DASHING:
		{
			m_tFrame.wstrStateKey = L"Dash";
			m_tFrame.fMaxFrame = 4;
			m_tInfo.vScale = _vec3(1.f, 1.f, 0.f);

		}
			break;
		case CPlayer::JUMPING:
		{
			m_tFrame.wstrStateKey = L"Jump1";
			m_tFrame.fMaxFrame = 2;
			m_tInfo.vScale = _vec3(1.f, 1.f, 0.f);

		}
			break;
		case CPlayer::DOUBLEJUMPING:
		{
			m_tFrame.wstrStateKey = L"Jump2";
			m_tFrame.fMaxFrame = 7;
			m_tInfo.vScale = _vec3(1.f, 1.f, 0.f);

		}
			break;
		case CPlayer::SLIDING:
		{
			m_tFrame.wstrStateKey = L"Sliding";
			m_tFrame.fMaxFrame = 3;
			m_tInfo.vScale = _vec3(1.f, 1.f, 0.f);

		}
			break;
		case CPlayer::HIT:
		{
			m_tFrame.wstrStateKey = L"Hit";
			m_tFrame.fMaxFrame = 0;
			m_tInfo.vScale = _vec3(1.f, 1.f, 0.f);

		}
			break;
		case CPlayer::DEAD:
		{
			m_tFrame.wstrStateKey = L"Dead";
			m_tFrame.fMaxFrame = 9;
			m_tInfo.vScale = _vec3(1.f, 1.f, 0.f);

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
