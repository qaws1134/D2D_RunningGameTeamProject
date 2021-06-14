#include "stdafx.h"
#include "Texture_Manager.h"
#include "Single_Texture.h"
#include "Multi_Texture.h"


IMPLEMENT_SINGLETON(CTexture_Manager)
CTexture_Manager::CTexture_Manager()
{
}


CTexture_Manager::~CTexture_Manager()
{
	Release();
}

HRESULT CTexture_Manager::Insert_Texture(const wstring & wstrObjKey, 
	const TEXID::ID& eID, const wstring & wstrFilePath, 
	const wstring & wstrStateKey, const int & iCount)
{
	auto& iter_find = m_mapTexture.find(wstrObjKey);

	if (iter_find == m_mapTexture.end())
	{
		CTexture* pTex = nullptr;

		switch (eID)
		{
		case TEXID::TEX_SINGLE:
			pTex = new CSingle_Texture;
			break;
		case TEXID::TEX_MULTI:
			pTex = new CMulti_Texture;
			break;
		}

		if (FAILED(pTex->Insert_Texture(wstrFilePath, wstrStateKey, iCount)))
		{
			wstring wstrErr = wstrObjKey + L"Create Failed";
			ERR_MSG(wstrErr.c_str());
			return E_FAIL;
		}

		m_mapTexture.emplace(wstrObjKey, pTex);
	}
	else if (TEXID::TEX_MULTI == eID)
	{
		if (FAILED(m_mapTexture[wstrObjKey]->Insert_Texture(wstrFilePath, wstrStateKey, iCount)))
			return E_FAIL;
		
	}
	return S_OK;
}

const TEXINFO * CTexture_Manager::Get_TexInfo(const wstring & wstrObjKey, const wstring & wstrStateKey, const int & iCount)
{
	auto& iter = m_mapTexture.find(wstrObjKey);

	if (m_mapTexture.end() == iter)
		return nullptr;


	return iter->second->Get_TexInfo(wstrStateKey, iCount);

}

void CTexture_Manager::Release(void)
{
	for (auto& Pair : m_mapTexture)
		Safe_Delete(Pair.second);

	m_mapTexture.clear();
}
