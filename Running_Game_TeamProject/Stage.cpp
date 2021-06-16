#include "stdafx.h"
#include "Stage.h"
#include "Player.h"
#include "Obj_Manager.h"
#include "Texture_Manager.h"
#include "FieldHurdle.h"
#include "Terrain.h"
#include "LineMgr.h"
#include "Scroll_Manager.h"
#include "KeyMgr.h"
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

	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/Bullet/%d.png", L"Bullet", 8);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/Celling/%d.png", L"Celling", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/Floor/%d.png", L"Floor", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/HighHill/%d.png", L"HighHill", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/LowHill/%d.png", L"LowHill", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1Map", TEXID::TEX_SINGLE, L"../Resource/Map/1-1/Map/0.png");
	CTexture_Manager::Get_Instance()->Insert_Texture(L"EMPTY", TEXID::TEX_SINGLE, L"../Resource/Map/0.png");




	// 플레이어 생성 
	CObj*	pObj = nullptr;
	pObj = CPlayer::Create();
	NULL_CHECK_RETURN(pObj, E_FAIL);
	FAILED_CHECK_RETURN(CObj_Manager::Get_Instance()->Insert_Obj(OBJID::PLAYER, pObj), E_FAIL);


	//CObj*	Obj = nullptr;
	//Obj = CFieldHurdle::Create({100.f,100.f,0.f}, HURDLEID::LOWHILL);
	//NULL_CHECK_RETURN(Obj, E_FAIL);
	//FAILED_CHECK_RETURN(CObj_Manager::Get_Instance()->Insert_Obj(OBJID::OBSTACLE, Obj), E_FAIL);


	m_pTerrain = new CTerrain;
	FAILED_CHECK_RETURN(m_pTerrain->Ready_Terrain(), E_FAIL);

	m_pTerrain->Load_Terrain();
	CLineMgr::Get_Instance()->Load_Line();
	CObj_Manager::Get_Instance()->Set_Tile(m_pTerrain->Get_Tile());

	return S_OK;
}

void CStage::Update_Scene()
{

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScroll_Manager::Get_Instance()->Set_Scroll(_vec3{ -10.f,0.f,0.f });
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScroll_Manager::Get_Instance()->Set_Scroll(_vec3{ 10.f,0.f,0.f });
	


	CObj_Manager::Get_Instance()->Update_Object();
	
}

void CStage::LateUpdate_Scene()
{
	CObj_Manager::Get_Instance()->LateUpdate_Object();
}

void CStage::Render_Scene(void)
{
	CGraphic_Dev::Get_Instance()->Render_Begin();


	RenderMap();


	m_pTerrain->Render_Terrain();
	CLineMgr::Get_Instance()->Render();
	CObj_Manager::Get_Instance()->Render_Object();
	CGraphic_Dev::Get_Instance()->Render_End();
}

void CStage::Release_Scene(void)
{
	Safe_Delete(m_pTerrain);
	CLineMgr::Destroy_Instance();
	CScroll_Manager::Destroy_Instance();
	CObj_Manager::Get_Instance()->Destroy_Instance();
}

void CStage::RenderMap()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"1-1Map");
	_vec3 Scroll = CScroll_Manager::Get_Instance()->Get_Scroll();
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;
	_mat matScale, matTrans;
	D3DXMatrixScaling(&matScale, 2.5f, 2.5f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX+250, WINCY >> 1, 0.f);
	matScale *= matTrans;
	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&matScale);
	CGraphic_Dev::Get_Instance()->
		Get_Sprite()->
		Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX + Scroll.x*0.01f, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

CStage * CStage::Create(void)
{
	CStage*		pInstance = new CStage;
	if (FAILED(pInstance->Ready_Scene()))
		Safe_Delete(pInstance);

	return pInstance;
}
