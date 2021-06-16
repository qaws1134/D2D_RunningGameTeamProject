#include "stdafx.h"
#include "MainApp.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "Obj_Manager.h"
#include "Graphic_Dev.h"
#include "Texture_Manager.h"
#include "Subject.h"
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

	CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::STAGE);

	return S_OK;
}

void CMainApp::Update_MainApp(void)
{
	CSceneMgr::Get_Instance()->Update_Scene();
}

void CMainApp::LateUpdate_MainApp(void)
{
	CSceneMgr::Get_Instance()->LateUpdate_Scene();
}

void CMainApp::Render_MainApp(void)
{
	CGraphic_Dev::Get_Instance()->Render_Begin();

	CSceneMgr::Get_Instance()->Render_Scene();

	CGraphic_Dev::Get_Instance()->Render_End();
}

void CMainApp::Release_MainApp(void)
{

	
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CObj_Manager::Get_Instance()->Destroy_Instance();
	CSubject::Get_Instance()->Destroy_Instance();
	CTexture_Manager::Get_Instance()->Destroy_Instance();
	CGraphic_Dev::Get_Instance()->Destroy_Instance();
	
}

CMainApp * CMainApp::Create(void)
{
	CMainApp*		pInstance = new CMainApp;
	if (FAILED(pInstance->Ready_MainApp()))
		Safe_Delete(pInstance);

	return pInstance;
}
