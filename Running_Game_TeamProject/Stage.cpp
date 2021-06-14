#include "stdafx.h"
#include "Stage.h"


CStage::CStage()
{
}


CStage::~CStage()
{
}

HRESULT CStage::Ready_Scene()
{

	return S_OK;
}

void CStage::Update_Scene()
{
}

void CStage::LateUpdate_Scene()
{
}

void CStage::Render_Scene(void)
{
}

void CStage::Release_Scene(void)
{
}

CStage * CStage::Create(void)
{
	CStage*		pInstance = new CStage;
	if (FAILED(pInstance->Ready_Scene()))
		Safe_Delete(pInstance);

	return pInstance;
}
