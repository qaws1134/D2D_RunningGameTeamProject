#include "stdafx.h"
#include "Graphic_Dev.h"

IMPLEMENT_SINGLETON(CGraphic_Dev)
CGraphic_Dev::CGraphic_Dev()
	:m_pSDK(nullptr),
	m_pGraphicDev(nullptr),
	m_pSprite(nullptr),
	m_pLine(nullptr)
{
}

CGraphic_Dev::~CGraphic_Dev()
{
	Release_GraphicDev();
}

HRESULT CGraphic_Dev::Ready_GraphicDev(void)
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	D3DCAPS9 d3dcaps;
	ZeroMemory(&d3dcaps, sizeof(D3DCAPS9));

	//2. ��ġ�� ������ �����ϰ� 
	//D3DADAPTER_DEFAULT, ���ܵ����� ������ �׷��� ī���� ������ �����ϰڴ�.
	//HAL - Hardware Abstract Layer 
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps)))
	{
		ERR_MSG(L"m_pSDK Create FAILED!");
		return E_FAIL;
	}
	DWORD vp = 0; // ���ؽ� ���μ���  = ������ȯ + ��������
				  //HW//TRANSFORM//AND//LIGHT//
	if (d3dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; //��ǻ�Ͱ�. �������, ������, �ﺸ. 

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;// 0~ 255 
	d3dpp.BackBufferCount = 1; //���� ī��Ʈ�� ����Ʈ 1 + ���� �־��� ī��Ʈ ��ŭ . �׷��� 
							   // 1�� �־��ָ� �� 2�� ���ڴ�. ����۸� ����  ?? 

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	//D3DSWAPEFFECT_DISCARD - ����ü�� ����� ����ϰڴ� ��� ���� �ȴ�. 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = TRUE; //TRUE �� ��� â��� , FALSE �ϰ�� ��üȭ�� 
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	// Ǯ��ũ���϶� ��� ó���� �������� ���� ó����.. �̰� ��ǻ�Ͱ� �˾Ƽ� ���� ����. 
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//3. �� ������ ���� ��ġ�� �����ϴ� �İ�ü�� ������ ���̴�. 
	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pGraphicDev)))
	{
		ERR_MSG(L"CreateDevice FAILED!");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(m_pGraphicDev, &m_pSprite)))
	{
		ERR_MSG(L"CreateSprite FAILED!");
		return E_FAIL;
	}



	D3DXFONT_DESCW tFont;
	ZeroMemory(&tFont, sizeof(D3DXFONT_DESCW));

	tFont.Width = 20;
	tFont.Height = 20;
	tFont.Weight = FW_HEAVY;
	tFont.CharSet = HANGUL_CHARSET;
	lstrcpy(tFont.FaceName, L"�ü�");
	if (FAILED(D3DXCreateFontIndirectW(m_pGraphicDev, &tFont, &m_pFont)))
	{
		ERR_MSG(L"��Ʈ ���� ����!");

	if (FAILED(D3DXCreateLine(m_pGraphicDev, &m_pLine)))
	{
		ERR_MSG(L"CreateLine FAILED!");

		return E_FAIL;
	}

	return S_OK;
}

void CGraphic_Dev::Release_GraphicDev(void)
{
	Safe_Release(m_pFont);
	Safe_Release(m_pSprite);
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pSDK);
}

void CGraphic_Dev::Render_Begin(void)
{
	m_pGraphicDev->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.f, 0.f, 1.f, 1.f), 0.f, 0);

	m_pGraphicDev->BeginScene();

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CGraphic_Dev::Render_End(HWND hWnd)
{
	m_pSprite->End();
	m_pGraphicDev->EndScene();
	m_pGraphicDev->Present(nullptr, nullptr, hWnd, nullptr);
}
