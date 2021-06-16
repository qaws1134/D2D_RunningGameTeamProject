#include "stdafx.h"
#include "MyMenu.h"
#include "SceneMgr.h"
#include "Texture_Manager.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
}

HRESULT CMyMenu::Ready_Scene()
{

	CTexture_Manager::Get_Instance()->Insert_Texture(L"Logo", TEXID::TEX_SINGLE, L"../Resource/Logo/Logo.jpg");
	m_vPos = _vec3(WINCX >> 1, WINCY >> 1, 0.f);
	m_vScale = _vec3(1.f, 1.f, 0.f);
	return S_OK;
}

void CMyMenu::Update_Scene()
{
	D3DXMatrixIdentity(&m_matWorld);

	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);
	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);

	m_matWorld = m_matScale * m_matTrans;



	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::STAGE);

}

void CMyMenu::LateUpdate_Scene()
{
}

void CMyMenu::Render_Scene(void)
{
	const TEXINFO*	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Logo");

	NULL_CHECK_RETURN(pTexInfo, );

	_vec3 vCenter = _vec3(pTexInfo->tImageInfo.Width * 0.5f, pTexInfo->tImageInfo.Height * 0.5f, 0.f);


	CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&m_matWorld);

	CGraphic_Dev::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

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
