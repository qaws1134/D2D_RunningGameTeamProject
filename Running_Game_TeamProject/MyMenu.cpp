#include "stdafx.h"
#include "MyMenu.h"
#include "SceneMgr.h"
#include "Texture_Manager.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	// 주석데스네
}

HRESULT CMyMenu::Ready_Scene()
{

	CTexture_Manager::Get_Instance()->Insert_Texture(L"Logo", TEXID::TEX_SINGLE, L"../Resource/Logo/Logo.jpg");

	return S_OK;
}

void CMyMenu::Update_Scene()
{
	m_vPos = _vec3(WINCX >> 1, WINCY >> 1, 0.f);
	m_vScale = _vec3(1.f, 1.f, 0.f);

}

void CMyMenu::LateUpdate_Scene()
{
}

void CMyMenu::Render_Scene(void)
{
}

void CMyMenu::Release_Scene(void)
{
}

CMyMenu * CMyMenu::Create(void)
{
	CMyMenu*		pInstance = new CMyMenu;
	if (FAILED(pInstance->Ready_Scene()))
		Safe_Delete(pInstance);

	return pInstance;
}
