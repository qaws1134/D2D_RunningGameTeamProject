#include "stdafx.h"
#include "Stage.h"
#include "Player.h"
#include "Obj_Manager.h"
#include "Texture_Manager.h"
CStage::CStage()
{
}


CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{


	// 텍스쳐 로딩 먼저
	
	// 플레이어
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Dash/%d.png", L"Dash", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Dead/%d.png", L"Dead", 9);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Hit/%d.png", L"Hit", 1);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Jump1/%d.png", L"Jump1", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Jump2/%d.png", L"Jump2", 7);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Run/%d.png", L"Run", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Sliding/%d.png", L"Sliding", 3);









	CObj*	pObj = nullptr;

	// 플레이어 생성 
	pObj = CPlayer::Create();
	NULL_CHECK_RETURN(pObj, E_FAIL);
	FAILED_CHECK_RETURN(CObj_Manager::Get_Instance()->Insert_Obj(OBJID::PLAYER, pObj), E_FAIL);





	return S_OK;
}

void CStage::Update_Scene()
{
	CObj_Manager::Get_Instance()->Update_Object();
}

void CStage::LateUpdate_Scene()
{
	CObj_Manager::Get_Instance()->LateUpdate_Object();
}

void CStage::Render_Scene(void)
{
	CObj_Manager::Get_Instance()->Render_Object();
}

void CStage::Release_Scene(void)
{
	CObj_Manager::Get_Instance()->Destroy_Instance();
}

CStage * CStage::Create(void)
{
	CStage*		pInstance = new CStage;
	if (FAILED(pInstance->Ready_Scene()))
		Safe_Delete(pInstance);

	return pInstance;
}
