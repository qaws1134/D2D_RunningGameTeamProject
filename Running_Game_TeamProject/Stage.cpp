#include "stdafx.h"
#include "Stage.h"
#include "Player.h"
#include "Item.h"
#include "Obj_Manager.h"
#include "Texture_Manager.h"
#include "FieldHurdle.h"
#include "HealthIcon.h"
#include "HealthBar.h"
#include "JellyScore.h"
#include "CoinScore.h"
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
	// �ؽ��� �ε� ����
	
	// �÷��̾�
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Dash/%d.png", L"Dash", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Dead/%d.png", L"Dead", 9);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Hit/%d.png", L"Hit", 1);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Jump1/%d.png", L"Jump1", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Jump2/%d.png", L"Jump2", 7);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Run/%d.png", L"Run", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Player", TEXID::TEX_MULTI, L"../Resource/Player/Sliding/%d.png", L"Sliding", 3);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ������ �̹��� �ε�
	// ����
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Gold/Big/%d.png", L"GoldCoin_Big", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Gold/Small/%d.png", L"GoldCoin_Small", 6);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Silver/Big/%d.png", L"SilverCoin_Big", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Silver/Small/%d.png", L"SilverCoin_Small", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/TransCoin/%d.png", L"TransCoin", 4);


	// ��ȭ �� ȸ�� ������
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Biggest/%d.png", L"Biggest", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Dash/%d.png", L"Dash", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Energy/Big/%d.png", L"Energy_Big", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Energy/Small/%d.png", L"Energy_Small", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Magnet/%d.png", L"Magnet", 4);



	// ����
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/1-1/%d.png", L"Jelly_1", 20);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/1-2/%d.png", L"Jelly_2", 20);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/1-3/%d.png", L"Jelly_3", 10);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/bear_jelly/%d.png", L"Jelly_Bear", 19);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/TransJelly/%d.png", L"TransJelly", 4);





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	// UI �̹��� �ε�

	CTexture_Manager::Get_Instance()->Insert_Texture(L"HealthIcon", TEXID::TEX_SINGLE, L"../Resource/UI/HealthIcon.png");
	CTexture_Manager::Get_Instance()->Insert_Texture(L"HealthBar", TEXID::TEX_SINGLE, L"../Resource/UI/HealthBar.png");



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	// ��ֹ�
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/Bullet/%d.png", L"Bullet", 8);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/Celling/%d.png", L"Celling", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/Floor/%d.png", L"Floor", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/HighHill/%d.png", L"HighHill", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1", TEXID::TEX_MULTI, L"../Resource/Map/1-1/LowHill/%d.png", L"LowHill", 2);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"1-1Map", TEXID::TEX_SINGLE, L"../Resource/Map/1-1/Map/0.png");
	CTexture_Manager::Get_Instance()->Insert_Texture(L"EMPTY", TEXID::TEX_SINGLE, L"../Resource/Map/0.png");




	// �÷��̾� ���� 
	CObj*	pObj = nullptr;
	pObj = CPlayer::Create();
	NULL_CHECK_RETURN(pObj, E_FAIL);
	FAILED_CHECK_RETURN(CObj_Manager::Get_Instance()->Insert_Obj(OBJID::PLAYER, pObj), E_FAIL);


	m_pTerrain = new CTerrain;
	FAILED_CHECK_RETURN(m_pTerrain->Ready_Terrain(), E_FAIL);

	m_pTerrain->Load_Terrain();
	CLineMgr::Get_Instance()->Load_Line();
	CObj_Manager::Get_Instance()->Set_Tile(m_pTerrain->Get_Tile());
	


	// ������ ����
	pObj = CItem::Create(ITEMID::ENERGY_SMALL);
	NULL_CHECK_RETURN(pObj, E_FAIL);
	FAILED_CHECK_RETURN(CObj_Manager::Get_Instance()->Insert_Obj(OBJID::ITEM, pObj), E_FAIL);



	// UI
	pObj = CHealthBar::Create();
	NULL_CHECK_RETURN(pObj, E_FAIL);
	FAILED_CHECK_RETURN(CObj_Manager::Get_Instance()->Insert_Obj(OBJID::UI, pObj), E_FAIL);
	pObj = CHealthIcon::Create();
	NULL_CHECK_RETURN(pObj, E_FAIL);
	FAILED_CHECK_RETURN(CObj_Manager::Get_Instance()->Insert_Obj(OBJID::UI, pObj), E_FAIL);
	pObj = CJellyScore::Create();
	NULL_CHECK_RETURN(pObj, E_FAIL);
	FAILED_CHECK_RETURN(CObj_Manager::Get_Instance()->Insert_Obj(OBJID::UI, pObj), E_FAIL);
	pObj = CCoinScore::Create();
	NULL_CHECK_RETURN(pObj, E_FAIL);
	FAILED_CHECK_RETURN(CObj_Manager::Get_Instance()->Insert_Obj(OBJID::UI, pObj), E_FAIL);





	// 이미지 세이브한거 불러옴
	Load_SavedImageObj();


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
	float fCenterX = (float)(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = (float)(pTexInfo->tImageInfo.Height >> 1);
	_mat matScale, matTrans;
	D3DXMatrixScaling(&matScale, 2.5f, 2.5f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX+250, WINCY >> 1, 0.f);
	matScale *= matTrans;
	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&matScale);
	CGraphic_Dev::Get_Instance()->
		Get_Sprite()->
		Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX + Scroll.x*0.01f, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CStage::Load_SavedImageObj(void)
{
	HANDLE hFile = CreateFile(L"../Data/Item.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);


	if (INVALID_HANDLE_VALUE == hFile)
		return;


	CObj_Manager::Get_Instance()->Release_List(OBJID::ITEM);

	DWORD dwByte = 0;
	_vec3 vPos = _vec3(0.f, 0.f, 0.f);
	ITEMID::ID eItemID = ITEMID::END;
	int iIndex = 0;

	CObj*	pItem = nullptr;

	while (true)
	{
		ReadFile(hFile, &vPos, sizeof(_vec3), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		ReadFile(hFile, &eItemID, sizeof(ITEMID::ID), &dwByte, nullptr);
		ReadFile(hFile, &iIndex, sizeof(int), &dwByte, nullptr);


		pItem = CItem::Create(eItemID, iIndex);
		pItem->Set_Pos(vPos);
		CObj_Manager::Get_Instance()->Insert_Obj(OBJID::ITEM, pItem);
	}


	CloseHandle(hFile);

}

CStage * CStage::Create(void)
{
	CStage*		pInstance = new CStage;
	if (FAILED(pInstance->Ready_Scene()))
		Safe_Delete(pInstance);

	return pInstance;
}
