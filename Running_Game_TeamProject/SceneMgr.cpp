#include "stdafx.h"
#include "SceneMgr.h"
#include "Stage.h"
#include "MyMenu.h"
#include "MyEdit.h"
IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_ePreScene(END), m_eCurScene(CSceneMgr::END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release_Scene();
}

void CSceneMgr::Update_Scene()
{
	m_pScene->Update_Scene();
}

void CSceneMgr::LateUpdate_Scene()
{
	m_pScene->LateUpdate_Scene();
}

void CSceneMgr::Render_Scene(void)
{
	m_pScene->Render_Scene();
}

void CSceneMgr::Release_Scene()
{
	Safe_Delete(m_pScene);
}

void CSceneMgr::Scene_Change(SCENEID _eID)
{
	m_eCurScene = _eID;

	if (m_ePreScene != m_eCurScene)
	{
		Release_Scene();

		switch (_eID)
		{
		case CSceneMgr::LOGO:
			break;
		case CSceneMgr::MENU:
			m_pScene = CMyMenu::Create();
			break;
		case CSceneMgr::EDIT:
			m_pScene = CMyEdit::Create();
			break;

		case CSceneMgr::STAGE:
			m_pScene = CStage::Create();
			break;
		default:
			break;
		}

		m_ePreScene = m_eCurScene;
	}
}
