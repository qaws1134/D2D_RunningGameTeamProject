#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"
#include "Scroll_Manager.h"
#include "Obj_Manager.h"
#include "Obj.h"
IMPLEMENT_SINGLETON(CLineMgr)
CLineMgr::CLineMgr() : m_bCheck(false), m_bEnd(false)
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{


}

void CLineMgr::Render()
{
	for (auto& pLine : m_listLine)
		pLine->Render();
}

void CLineMgr::Release()
{
	for_each(m_listLine.begin(), m_listLine.end(), Safe_Delete<CLine*>);
	m_listLine.clear();
}

bool CLineMgr::Collision_Line(float _x, float* _y)
{
	_vec3 Scroll = CScroll_Manager::Get_Instance()->Get_Scroll();
	if (m_listLine.empty())
		return false;

	float fPlayerSizeY = CObj_Manager::Get_Instance()->Get_List(OBJID::PLAYER)->front()->Get_Info().vSize.y*0.5f;

	for (auto& pLine : m_listLine)
	{
		if (CObj_Manager::Get_Instance()->Get_List(OBJID::PLAYER)->front()->Get_Info().vPos.y + fPlayerSizeY+10.f < pLine->Get_Info().LPos.y)
			return false;
		if (pLine->Get_Info().LPos.x - Scroll.x < _x
			&& pLine->Get_Info().RPos.x - Scroll.x > _x)
		{
			float x1 = pLine->Get_Info().LPos.x;
			float y1 = pLine->Get_Info().LPos.y;
			float x2 = pLine->Get_Info().RPos.x;
			float y2 = pLine->Get_Info().RPos.y;

			*_y = ((y2 - y1) / (x2 - x1)) * (_x - x1) + y1 - fPlayerSizeY;//플레이어 y값

			return true;
		}
		
	}

	return false;	
}

void CLineMgr::Picking_Line()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x += (LONG)(CScroll_Manager::Get_Instance()->Get_Scroll().x);
	int iDiv= (int)0.f;
	if (m_bCheck)
	{
		m_tLinePos[0].x = (float)pt.x;
		m_tLinePos[0].y = (WINCY-(WINCY *0.5f)*0.33f);	//ypos고정
		
		iDiv = (int)m_tLinePos[0].x % TILECX;
		m_tLinePos[0].x =m_tLinePos[0].x - (float)iDiv;	

		m_bCheck = !m_bCheck;
	}
	else
	{
		m_tLinePos[1].x = (float)pt.x;
		m_tLinePos[1].y = (WINCY - (WINCY *0.5f)*0.33f);
		iDiv = (int)m_tLinePos[1].x % TILECX;

		m_tLinePos[1].x= m_tLinePos[1].x - (float)iDiv;	


		m_listLine.emplace_back(new CLine(m_tLinePos[0], m_tLinePos[1]));

		//키고 찍으면 다시 0으로 돌아감
		if (!m_bEnd)
		{
			m_tLinePos[0].x = m_tLinePos[1].x;
			m_tLinePos[0].y = m_tLinePos[1].y;
		}
		else
		{
			m_bCheck = !m_bCheck;
			m_bEnd = false;
		}
	}





}

void CLineMgr::Save_Line()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		//MessageBox(g_hWnd, L"저장실패", L"실패", MB_OKCANCEL);
		return;
	}
	DWORD dwByte = 0;

	for (auto& pLine : m_listLine)
		WriteFile(hFile, &pLine->Get_Info(), sizeof(LINEINFO), &dwByte, NULL);

	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"저장 성공", L"성공", MB_OKCANCEL);
}

void CLineMgr::Load_Line()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		//MessageBox(g_hWnd, L"불러오기 실패", L"실패", MB_OK);
		return;
	}

	Release();
	LINEINFO tTemp;
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(LINEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_listLine.emplace_back(new CLine(tTemp.LPos, tTemp.RPos));
	}
	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"불러오기 성공", L"성공", MB_OK);

}
