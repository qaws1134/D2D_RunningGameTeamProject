#include "stdafx.h"
#include "Graphic_Dev.h"

IMPLEMENT_SINGLETON(CGraphic_Dev)
CGraphic_Dev::CGraphic_Dev()
	:m_pSDK(nullptr),
	m_pGraphicDev(nullptr),
	m_pSprite(nullptr)
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

	//2. 장치의 수준을 조사하고 
	//D3DADAPTER_DEFAULT, 진단도구에 나열된 그래픽 카드의 정보를 조사하겠다.
	//HAL - Hardware Abstract Layer 
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps)))
	{
		ERR_MSG(L"m_pSDK Create FAILED!");
		return E_FAIL;
	}
	DWORD vp = 0; // 버텍스 프로세싱  = 정점변환 + 조명연산
				  //HW//TRANSFORM//AND//LIGHT//
	if (d3dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; //컴퓨터가. 세종대왕, 진돗개, 삼보. 

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;// 0~ 255 
	d3dpp.BackBufferCount = 1; //여기 카운트는 디폴트 1 + 내가 넣어준 카운트 만큼 . 그래서 
							   // 1을 넣어주면 총 2개 쓰겠다. 백버퍼를 ㅇㅋ  ?? 

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	//D3DSWAPEFFECT_DISCARD - 스왑체인 방식을 사용하겠다 라는 뜻이 된다. 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = TRUE; //TRUE 일 경우 창모드 , FALSE 일경우 전체화면 
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	// 풀스크린일때 어떻게 처리할 것인지에 대한 처리드.. 이건 컴퓨터가 알아서 해줄 문제. 
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//3. 그 수준을 토대로 장치를 제어하는 컴객체를 생성할 것이다. 
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

	return S_OK;
}

void CGraphic_Dev::Release_GraphicDev(void)
{
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
