#include "stdafx.h"
#include "Single_Texture.h"


CSingle_Texture::CSingle_Texture()
{
}


CSingle_Texture::~CSingle_Texture()
{
	Release();
}

const TEXINFO * CSingle_Texture::Get_TexInfo(const wstring & wstrStateKey, const int & iCount)
{
	return m_pTexInfo;
}

HRESULT CSingle_Texture::Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey, const int & iCount)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_pTexInfo->tImageInfo)))
	{
		wstring wstrErrMessage = wstrFilePath + L"Load Failed";
		ERR_MSG(wstrErrMessage.c_str());
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFileEx(
		CGraphic_Dev::Get_Instance()->Get_Device(),
		wstrFilePath.c_str(),
		m_pTexInfo->tImageInfo.Width,
		m_pTexInfo->tImageInfo.Height,
		m_pTexInfo->tImageInfo.MipLevels,
		0,
		m_pTexInfo->tImageInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0,
		&m_pTexInfo->tImageInfo,
		nullptr,
		&m_pTexInfo->pTexture)))
	{
		wstring wstrErr_Message = wstrFilePath + L"CreateTexture Failed";
		ERR_MSG(wstrErr_Message.c_str());
		return E_FAIL;
	}
	return S_OK;
}

void CSingle_Texture::Release()
{
	Safe_Release(m_pTexInfo->pTexture);
	Safe_Delete(m_pTexInfo);
}

