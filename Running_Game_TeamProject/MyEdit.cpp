#include "stdafx.h"
#include "MyEdit.h"
#include "Obj_Manager.h"
#include "Texture_Manager.h"
#include "FieldHurdle.h"
#include "KeyMgr.h"
#include "Scroll_Manager.h"
#include "Terrain.h"
#include "LineMgr.h"
#include "Item.h"

CMyEdit::CMyEdit():m_pTerrain(nullptr), m_iID(0), m_bSwapLine_Or_Hurdle(false), m_pItem(nullptr), m_iItemIndex(0),
m_eItemID(ITEMID::END), m_vItemPos(_vec3())
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




	/////////////////////// 아이템 이미지 추가 ////////////////////////////////////////////////////////////////////////////////////////////


	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Gold/Big/%d.png", L"GoldCoin_Big", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Gold/Small/%d.png", L"GoldCoin_Small", 6);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Silver/Big/%d.png", L"SilverCoin_Big", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Coin/Silver/Small/%d.png", L"SilverCoin_Small", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/TransCoin/%d.png", L"TransCoin", 4);



	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Biggest/%d.png", L"Biggest", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Dash/%d.png", L"Dash", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Energy/Big/%d.png", L"Energy_Big", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Energy/Small/%d.png", L"Energy_Small", 4);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Magnet/%d.png", L"Magnet", 4);




	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/1-1/%d.png", L"Jelly_1", 20);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/1-2/%d.png", L"Jelly_2", 20);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/1-3/%d.png", L"Jelly_3", 10);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/Jelly/bear_jelly/%d.png", L"Jelly_Bear", 19);
	CTexture_Manager::Get_Instance()->Insert_Texture(L"Item", TEXID::TEX_MULTI, L"../Resource/Item/TransJelly/%d.png", L"TransJelly", 4);





	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	m_pTerrain = new CTerrain;
	FAILED_CHECK_RETURN(m_pTerrain->Ready_Terrain(), E_FAIL);

	return S_OK;
}

void CMyEdit::Update_Scene()
{
	Key_Input();

	for (auto& pItem : m_listItem)
	{
		pItem->Update_Object();
	}
}

void CMyEdit::LateUpdate_Scene()
{
	for (auto& pItem : m_listItem)
		pItem->Setting_TexInfo();
}

void CMyEdit::Render_Scene(void)
{
	CGraphic_Dev::Get_Instance()->Render_Begin();
	CObj_Manager::Get_Instance()->Render_Object();
	m_pTerrain->Render_Terrain();
	CLineMgr::Get_Instance()->Render();


	for (auto& pItem : m_listItem)
		pItem->Render_Object();

	CGraphic_Dev::Get_Instance()->Render_End();
}

void CMyEdit::Release_Scene(void)
{
	Safe_Delete(m_pTerrain);
	CLineMgr::Destroy_Instance();
	CScroll_Manager::Destroy_Instance();
	
	for (auto& pItem : m_listItem)
		Safe_Delete(pItem);

	m_listItem.clear();
}

CMyEdit * CMyEdit::Create()
{
	CMyEdit* pInstance = new CMyEdit;
	if (FAILED(pInstance->Ready_Scene()))
		Safe_Delete(pInstance);

	return pInstance;
}


void CMyEdit::Save_ItemList()
{



	HANDLE hFile = CreateFile(L"../Data/Item.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD dwByte = 0;





	_vec3 vPos = _vec3(0.f, 0.f, 0.f);
	ITEMID::ID eItemID = ITEMID::END;
	int iIndex = 0;

	for (auto& pItem : m_listItem)
	{
		vPos = pItem->Get_Info().vPos;



		WriteFile(hFile, &vPos, sizeof(_vec3), &dwByte, nullptr);
		WriteFile(hFile, &static_cast<CItem*>(pItem)->Get_ItemID(), sizeof(ITEMID::ID), &dwByte, nullptr);

		int iIndex = (int)(pItem->Get_Frame().fStartFrame);

		WriteFile(hFile, &iIndex, sizeof(int), &dwByte, nullptr);

	}

	CloseHandle(hFile);
}

void CMyEdit::Load_ItemList()
{
	HANDLE hFile = CreateFile(L"../Data/Item.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);


	if (INVALID_HANDLE_VALUE == hFile)
		return;

	for (auto& pItem : m_listItem)
		Safe_Delete(pItem);
	m_listItem.clear();
	
	DWORD dwByte = 0;
	_vec3 vPos = _vec3(0.f, 0.f, 0.f);
	ITEMID::ID eItemID = ITEMID::END;
	int iIndex = 0;

	m_pItem = nullptr;

	while (true)
	{
		ReadFile(hFile, &vPos, sizeof(_vec3), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		
		ReadFile(hFile, &eItemID, sizeof(ITEMID::ID), &dwByte, nullptr);
		ReadFile(hFile, &iIndex, sizeof(int), &dwByte, nullptr);


		m_pItem = CItem::Create(eItemID, iIndex);
		m_pItem->Set_Pos(vPos);
		m_listItem.emplace_back(m_pItem);
	}


	CloseHandle(hFile);

}


void CMyEdit::Key_Input(void)
{


	////////////////////////////////////////// 영렬이꺼 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScroll_Manager::Get_Instance()->Set_Scroll(_vec3{ -20.f,0.f,0.f });
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScroll_Manager::Get_Instance()->Set_Scroll(_vec3{ 20.f,0.f,0.f });


	//if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD0))
	//{
	//	m_iID = 0;
	//}
	//if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD1))
	//{
	//	m_iID = 1;
	//}
	//if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD2))
	//{
	//	m_iID = 2;
	//}
	//if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD3))
	//{
	//	m_iID = 3;
	//}
	//if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD4))
	//{
	//	m_iID = 4;
	//}
	//if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD5))
	//{
	//	m_iID = 5;
	//}

	/*if (!m_bSwapLine_Or_Hurdle)
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
	}*/


	//if (CKeyMgr::Get_Instance()->Key_Down('A'))
	//{
	//	//m_pTerrain->Save_Terrain();
	//}
	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		m_pTerrain->Load_Terrain();
	}
/*
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
	}*/

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











	//////////////////////////////////////////////// 내꺼 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// 왼쪽 클릭시 아이템 배치
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{

	

		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		if (0 > pt.x || pt.x > WINCX ||
			0 > pt.y || pt.y > WINCY)
			return;

		_vec3 vScroll = CScroll_Manager::Get_Instance()->Get_Scroll();
		m_vItemPos = _vec3((float)pt.x + vScroll.x, (float)pt.y + vScroll.y, 0.f);


		if (m_eItemID == ITEMID::END)
			return;

		m_pItem = CItem::Create(m_eItemID, m_iItemIndex);
		NULL_CHECK_RETURN(m_pItem, );
		
		m_pItem->Set_Pos(m_vItemPos);


		m_listItem.push_back(m_pItem);
	}






	if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
	{
		m_listItem.back()->Set_Dead();
	}








	//// 강화템

	if (GetAsyncKeyState('Y') & 0x8000)
		m_eItemID = ITEMID::DASH;

	if (GetAsyncKeyState('U') & 0x8000)
		m_eItemID = ITEMID::BIGGEST;

	if (GetAsyncKeyState('I') & 0x8000)
		m_eItemID = ITEMID::MAGNET;

	if (GetAsyncKeyState('O') & 0x8000)
		m_eItemID = ITEMID::ENERGY_BIG;

	if (GetAsyncKeyState('P') & 0x8000)
		m_eItemID = ITEMID::ENERGY_SMALL;






	//// 젤리

	if (GetAsyncKeyState('Q') & 0x8000)
		m_eItemID = ITEMID::JELLY_1;

	if (GetAsyncKeyState('W') & 0x8000)
		m_eItemID = ITEMID::JELLY_2;

	if (GetAsyncKeyState('E') & 0x8000)
		m_eItemID = ITEMID::JELLY_3;

	if (GetAsyncKeyState('R') & 0x8000)
		m_eItemID = ITEMID::JELLY_BEAR;


	// 코인
	if (GetAsyncKeyState('H') & 0x8000)
		m_eItemID = ITEMID::GOLDCOIN_BIG;

	if (GetAsyncKeyState('J') & 0x8000)
		m_eItemID = ITEMID::GOLDCOIN_SMALL;

	if (GetAsyncKeyState('K') & 0x8000)
		m_eItemID = ITEMID::SILVERCOIN_BIG;

	if (GetAsyncKeyState('L') & 0x8000)
		m_eItemID = ITEMID::SILVERCOIN_SMALL;







	// 아이템 인덱스관련
	if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
		m_iItemIndex = 0;


	if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
		m_iItemIndex = 1;


	if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
		m_iItemIndex = 2;


	if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
		m_iItemIndex = 3;


	if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
		m_iItemIndex = 4;


	if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
		m_iItemIndex = 5;


	if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
		m_iItemIndex = 6;


	if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
		m_iItemIndex = 7;


	if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
		m_iItemIndex = 8;


	if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
		m_iItemIndex = 9;


	// 아이템 세이브 로드

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
		Save_ItemList();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
		Load_ItemList();



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





}
