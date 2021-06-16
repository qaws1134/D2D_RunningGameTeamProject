#include "stdafx.h"
#include "MyMenu.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
}

HRESULT CMyMenu::Ready_Scene()
{
	return E_NOTIMPL;
}

void CMyMenu::Update_Scene()
{
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
