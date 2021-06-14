#include "stdafx.h"
#include "Multi_Texture.h"


CMulti_Texture::CMulti_Texture()
{
}


CMulti_Texture::~CMulti_Texture()
{
	Release();
}

const TEXINFO * CMulti_Texture::Get_TexInfo(const wstring & wstrStateKey, const int & iCount)
{
	auto& iter_find = m_mapMulti.find(wstrStateKey);
	if (iter_find == m_mapMulti.end())
		return nullptr;
	if (iter_find->second.size() <= (size_t)iCount)
		return nullptr;

	return m_mapMulti[wstrStateKey][iCount];
	return iter_find->second[iCount];
}

HRESULT CMulti_Texture::Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey, const int & iCount)
{
	auto& iter_find = m_mapMulti.find(wstrStateKey);

	if (iter_find != m_mapMulti.end())
	{
		wstring wstrErr = wstrStateKey + L"있지롱!~";
		ERR_MSG(wstrErr.c_str());
		return E_FAIL;
	}


	TCHAR szFilePath[MAX_PATH] = L"";

	for (int i = 0; i < iCount; ++i)
	{
		wsprintf(szFilePath, wstrFilePath.c_str(), i);
		TEXINFO* pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		if (FAILED(D3DXGetImageInfoFromFile(szFilePath, &pTexInfo->tImageInfo)))
		{
			wstring wstrERR = wstring(szFilePath) + L"의묵이는 말을 존나 막한다.. 존나 상처... ";
			ERR_MSG(wstrERR.c_str());
			return E_FAIL;
		}


		if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Dev::Get_Instance()->Get_Device(),
			szFilePath, pTexInfo->tImageInfo.Width,
			pTexInfo->tImageInfo.Height,
			pTexInfo->tImageInfo.MipLevels,
			0,
			pTexInfo->tImageInfo.Format,
			D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &pTexInfo->tImageInfo, nullptr, &pTexInfo->pTexture

		)))
		{
			Safe_Delete(pTexInfo);
			return E_FAIL;
		}

		m_mapMulti[wstrStateKey].emplace_back(pTexInfo);
	}

	return S_OK;
}

void CMulti_Texture::Release()
{
	for (auto& pVector : m_mapMulti)
	{
		for (auto& pTexInfo : pVector.second)
		{
			Safe_Release(pTexInfo->pTexture);
			Safe_Delete(pTexInfo);
		}
		pVector.second.shrink_to_fit();
		pVector.second.clear();
	}

	m_mapMulti.clear();

}


