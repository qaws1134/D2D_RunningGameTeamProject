#include "stdafx.h"
#include "MyEdit.h"
#include "Obj_Manager.h"
#include "Texture_Manager.h"
#include "FieldHurdle.h"
#include "KeyMgr.h"
#include "Scroll_Manager.h"
#include "Terrain.h"
#include "LineMgr.h"



CMyEdit::CMyEdit():m_pTerrain(nullptr), m_iID(0), m_bSwapLine_Or_Hurdle(false)
{
}


CMyEdit::~CMyEdit()
{
	Release_Scene();
}

HRESULT CMyEdit::Ready_Scene()
{

	FAILED_CHECK_RETURN(CGraphic_Dev::Get_Instance()->Ready_GraphicDev(), E_FAIL);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/Bullet/%d.png", L"Bullet", 8);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/Celling/%d.png", L"Celling", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/Floor/%d.png", L"Floor", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/HighHill/%d.png", L"HighHill", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/LowHill/%d.png", L"LowHill", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1Map", TEXID::TEX_SINGLE, L"../Resource/Map/1-1/Map/0.png");
	CTexture_Manager::Get_Instance()->Insert_Texture(L"EMPTY", TEXID::TEX_SINGLE, L"../Resource/Map/0.png");


	m_pTerrain = new CTerrain;
	FAILED_CHECK_RETURN(m_pTerrain->Ready_Terrain(), E_FAIL);

	return S_OK;
}

void CMyEdit::Update_Scene()
{



	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScroll_Manager::Get_Instance()->Set_Scroll(_vec3{ -20.f,0.f,0.f });
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScroll_Manager::Get_Instance()->Set_Scroll(_vec3{ 20.f,0.f,0.f });

	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD0))
	{
		m_iID = 0;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD1))
	{
		m_iID = 1;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD2))
	{
		m_iID = 2;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD3))
	{
		m_iID = 3;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD4))
	{
		m_iID = 4;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD5))
	{
		m_iID = 5;
	}

	if (!m_bSwapLine_Or_Hurdle)
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			POINT point = {};
			GetCursorPos(&point);
			ScreenToClient(g_hWnd, &point);

			D3DXVECTOR3 vMouse{ float(point.x) + CScroll_Manager::Get_Instance()->Get_Scroll().x, float(point.y), 0.f };
			m_pTerrain->TilePicking_Terrain(vMouse, m_iID);
		}
	}
	else
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			CLineMgr::Get_Instance()->Picking_Line();
		}
	}


	if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		m_pTerrain->Save_Terrain();
	}
	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		m_pTerrain->Load_Terrain();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		CLineMgr::Get_Instance()->Save_Line();
	}
	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		CLineMgr::Get_Instance()->Load_Line();
	}


	if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		m_bSwapLine_Or_Hurdle = !m_bSwapLine_Or_Hurdle;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		CLineMgr::Get_Instance()->Set_End();
	}
	if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		CLineMgr::Get_Instance()->Back_Line();
	}



}

void CMyEdit::LateUpdate_Scene()
{
}

void CMyEdit::Render_Scene(void)
{
	CGraphic_Dev::Get_Instance()->Render_Begin();
	CObj_Manager::Get_Instance()->Render_Object();
	m_pTerrain->Render_Terrain();
	CLineMgr::Get_Instance()->Render();
	CGraphic_Dev::Get_Instance()->Render_End();
}

void CMyEdit::Release_Scene(void)
{
	Safe_Delete(m_pTerrain);
	CLineMgr::Destroy_Instance();
	CScroll_Manager::Destroy_Instance();
}

CMyEdit * CMyEdit::Create()
{
	CMyEdit* pInstance = new CMyEdit;
	if (FAILED(pInstance->Ready_Scene()))
		Safe_Delete(pInstance);

	return pInstance;
}
