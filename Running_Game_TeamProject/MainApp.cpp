#include "stdafx.h"
#include "MainApp.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "Obj_Manager.h"
#include "Graphic_Dev.h"

CMainApp::CMainApp()
{
}


CMainApp::~CMainApp()
{
	Release_MainApp();
}

HRESULT CMainApp::Ready_MainApp(void)
{
	FAILED_CHECK_RETURN(CGraphic_Dev::Get_Instance()->Ready_GraphicDev(), E_FAIL);



	return S_OK;
}

void CMainApp::Update_MainApp(void)
{
}

void CMainApp::LateUpdate_MainApp(void)
{
}

void CMainApp::Render_MainApp(void)
{
}

void CMainApp::Release_MainApp(void)
{

	
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CObj_Manager::Get_Instance()->Destroy_Instance();
	CGraphic_Dev::Get_Instance()->Destroy_Instance();

}

CMainApp * CMainApp::Create(void)
{
	CMainApp*		pInstance = new CMainApp;
	if (FAILED(pInstance->Ready_MainApp()))
		Safe_Delete(pInstance);

	return pInstance;
}
