#include "stdafx.h"
#include "Stage.h"
#include "Player.h"
#include "Obj_Manager.h"

CStage::CStage()
{
}


CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
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
	
}

CStage * CStage::Create(void)
{
	CStage*		pInstance = new CStage;
	if (FAILED(pInstance->Ready_Scene()))
		Safe_Delete(pInstance);

	return pInstance;
}
