#include "stdafx.h"
#include "Stage.h"
#include "Obj_Manager.h"
#include "Texture_Manager.h"
#include "Player.h"
#include "Item.h"

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


	// 아이템 이미지 로드
	// 코인
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Gold/Big/%d.png", L"GoldCoin_Big", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Gold/Small/%d.png", L"GoldCoin_Small", 6);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Silver/Big/%d.png", L"SilverCoin_Big", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Silver/Big/%d.png", L"SilverCoin_Small", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/TransCoin/%d.png", L"TransCoin", 4);

	
	// 강화 및 회복 아이템
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Biggest/%d.png", L"Biggest", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Dash/%d.png", L"Dash", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Energy/Big/%d.png", L"Energy_Big", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Energy/Small/%d.png", L"Energy_Small", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Magnet/%d.png", L"Magnet", 4);



	// 젤리
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/1-1/%d.png", L"Jelly_1", 20);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/1-2/%d.png", L"Jelly_2", 20);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/1-3/%d.png", L"Jelly_3", 10);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/bear_jelly/%d.png", L"Jelly_Bear", 19);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/TransJelly/%d.png", L"TransJelly", 4);








	CObj*	pObj = nullptr;

	// 플레이어 생성 
	pObj = CPlayer::Create();
	NULL_CHECK_RETURN(pObj, E_FAIL);
	FAILED_CHECK_RETURN(CObj_Manager::Get_Instance()->Insert_Obj(OBJID::PLAYER, pObj), E_FAIL);

	// 아이템 생성테스트
	pObj = CItem::Create(ITEMID::BIGGEST);
	NULL_CHECK_RETURN(pObj, E_FAIL);
	FAILED_CHECK_RETURN(CObj_Manager::Get_Instance()->Insert_Obj(OBJID::ITEM, pObj), E_FAIL);




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
