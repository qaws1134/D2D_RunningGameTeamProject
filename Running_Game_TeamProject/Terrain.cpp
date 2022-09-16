#include "stdafx.h"
#include "Terrain.h"
#include "Scroll_Manager.h"
#include "FieldHurdle.h"
#include "Texture_Manager.h"
CTerrain::CTerrain() : m_fOffsetY(0), bCollide(false),m_fAngle(0), m_fIncrese(0.f)
{
}


CTerrain::~CTerrain()
{
	Release_Terrain();
}

HRESULT CTerrain::Ready_Terrain()
{
	m_vecTile.reserve(TILEX * TILEY);
	float fX = 0.f, fY = 0.f;
	TILE* pTile = nullptr;
	for (size_t i = 0; i < TILEY; ++i)
	{
		for (size_t j = 0; j < TILEX; ++j)
		{
			fX = (float)(j * TILECX + (TILECX >> 1));
			fY = (float)(i * TILECY + (TILECY >> 1));
			pTile = new TILE;
			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { 1.f, 1.f, 1.f };
			pTile->byOption = 5;
			pTile->bPlayerCol = false;
			m_vecTile.emplace_back(pTile);
		}
	}


	return S_OK;
}

void CTerrain::Render_Terrain()
{
	D3DXMATRIX matScale, matTrans;
	int iSize = m_vecTile.size();
	vFlyDir = { 1.f,1.f,0.f };

	_vec3 iScroll = CScroll_Manager::Get_Instance()->Get_Scroll();

	for (int i = 0; i < iSize; ++i)
	{
		if (m_vecTile[i]->bPlayerCol)
		{
			m_vecTile[i]->byOption = 5;
		}

		Set_Tile(m_vecTile[i]->byOption);
		m_vecTile[i]->bCollide = bCollide;
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()
			->Get_TexInfo(m_tFrame.wstrObjKey, m_tFrame.wstrStateKey, (int)m_tFrame.fStartFrame);

		if (nullptr == pTexInfo)
			return;
		float fCenterX = (float)(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = (float)(pTexInfo->tImageInfo.Height >> 1);
		m_vecTile[i]->vScale = { fCenterX, fCenterY, 0.f };


		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x - iScroll.x, m_vecTile[i]->vPos.y + m_fOffsetY, 0.f);
		matScale *= matTrans;
		CGraphic_Dev::Get_Instance()->Get_Sprite()->SetTransform(&matScale);
		CGraphic_Dev::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &m_vecTile[i]->vScale, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}


void CTerrain::Release_Terrain()
{
	for (TILE*& pTile : m_vecTile)
		Safe_Delete(pTile);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTerrain::Set_Tile(int _iID)
{
	switch (_iID)
	{
	case 0:
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.wstrStateKey = L"Floor";
		m_fOffsetY = 0.f;
		m_eID = HURDLEID::FLOOR;
		m_tFrame.wstrObjKey = L"1-1";
		bCollide = false;
		break;
	case 1:
		m_tFrame.fStartFrame = 1.f;
		m_tFrame.wstrStateKey = L"Floor";
		m_fOffsetY = 0.f;
		m_eID = HURDLEID::FLOOR2F;
		m_tFrame.wstrObjKey = L"1-1";
		bCollide = false;
		break;
	case 2:
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.wstrStateKey = L"LowHill";
		m_fOffsetY = 10.f;
		m_eID = HURDLEID::LOWHILL;
		m_tFrame.wstrObjKey = L"1-1";
		bCollide = true;
		break;
	case 3:
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.wstrStateKey = L"HighHill";
		m_fOffsetY = -45.f;
		m_eID = HURDLEID::HIGHHILL;
		m_tFrame.wstrObjKey = L"1-1";
		bCollide = true;
		break;
	case 4:
		m_tFrame.fStartFrame = 0.f;
		m_tFrame.wstrStateKey = L"Celling";
		m_fOffsetY = 0.f;
		m_eID = HURDLEID::CELLING;
		m_tFrame.wstrObjKey = L"1-1";
		bCollide = true;
		break;
	case 5:
		m_eID = HURDLEID::EMPTY;
		m_tFrame.wstrObjKey = L"EMPTY";
		bCollide = false;
	default:
		break;
	}
}



void CTerrain::TilePicking_Terrain(const D3DXVECTOR3 & vMousePos, const BYTE & byOption)
{
	int x = (int)(vMousePos.x / TILECX);
	int y = (int)(vMousePos.y / TILECY);

	int iIndex = y*TILEX + x;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	m_vecTile[iIndex]->byOption = byOption;
}



void CTerrain::Save_Terrain()
{
	HANDLE hFile = CreateFile(L"../Data/Terrain.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"���� ����", L"����", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	for (auto& pTile : m_vecTile)
	{
		WriteFile(hFile, &pTile->byOption, sizeof(BYTE), &dwByte, NULL);
		WriteFile(hFile, &pTile->vPos, sizeof(_vec3), &dwByte, NULL);
		WriteFile(hFile, &pTile->vSize, sizeof(_vec3), &dwByte, NULL);
		WriteFile(hFile, &pTile->bCollide, sizeof(bool), &dwByte, NULL);
	}
	CloseHandle(hFile);
}

void CTerrain::Load_Terrain()
{
	HANDLE hFile = CreateFile(L"../Data/Terrain.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"�ҷ����� ����!", L"����", MB_OK);
		return;
	}

	Release_Terrain();

	DWORD	dwByte = 0;

	BYTE	byOption = 0;
	_vec3	vPos = {};
	_vec3	vSize = {};
	bool	bCollide = false;
	while (true)
	{
		ReadFile(hFile, &byOption, sizeof(BYTE), &dwByte, NULL);
		ReadFile(hFile, &vPos, sizeof(_vec3), &dwByte, NULL);
		ReadFile(hFile, &vSize, sizeof(_vec3), &dwByte, NULL);
		ReadFile(hFile, &bCollide, sizeof(bool), &dwByte, NULL);

		if (0 == dwByte)
			break;
		TILE* pTile = new TILE;
		pTile->byOption = byOption;
		pTile->vPos = vPos;
		pTile->vSize = vSize;
		pTile->bCollide = bCollide;
		pTile->bPlayerCol = false;



		m_vecTile.emplace_back(pTile);
	}

	CloseHandle(hFile);
}

