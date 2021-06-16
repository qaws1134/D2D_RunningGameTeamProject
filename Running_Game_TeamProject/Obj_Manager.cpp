#include "stdafx.h"
#include "Obj_Manager.h"
#include "Collision_Manager.h"
#include "SceneMgr.h"
#include "Obj.h"
#include "LineMgr.h"

IMPLEMENT_SINGLETON(CObj_Manager)

CObj_Manager::CObj_Manager()
{
}


CObj_Manager::~CObj_Manager()
{
	Release_Object();
}

HRESULT CObj_Manager::Ready_Object(void)
{
	return S_OK;
}

int CObj_Manager::Update_Object(void)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& iter = m_listObj[i].begin(); iter != m_listObj[i].end();)
		{
			int iResult = (*iter)->Update_Object();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}


	//플레이어 타일 충돌검사 
	CCollision_Manager::Collision_Rect_Obstacle(m_listObj[OBJID::PLAYER], m_vecObstacle);
	//플레이어 x 검사   플레이어 y 포인터로 값 변경
	//상식적으로 cosnt Get INFO인데  y값 변경이 안될것같은 느낌적인 느낌느낌???
	_vec3 PlayerPos = m_listObj[OBJID::PLAYER].front()->Get_Info().vPos;	
	CLineMgr::Get_Instance()->Collision_Line(PlayerPos.x, &PlayerPos.y);

	return 0;
}

void CObj_Manager::LateUpdate_Object(void)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			if (nullptr == pObj)
				continue;

			pObj->LateUpdate_Object();
		}

	}
}

void CObj_Manager::Render_Object(void)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			if (nullptr == pObj)
				continue;

			pObj->Render_Object();
		}
	}
}

void CObj_Manager::Release_Object(void)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

HRESULT CObj_Manager::Insert_Obj(const OBJID::ID & eID, CObj * pObj)
{

	NULL_CHECK_RETURN(pObj, E_FAIL);

	m_listObj[eID].push_back(pObj);


	return S_OK;
}




void CObj_Manager::Item_Acquired(ITEMID::ID eID)
{
	//if (m_listObj[OBJ_PLAYER].empty() || CPlayer::PLAYER_DEAD == static_cast<CPlayer*>(m_listObj[OBJ_PLAYER].front())->Get_State()) 
	//	return;


	//dynamic_cast<CPlayer*>(m_listObj[OBJ_PLAYER].front())->Item_AcQuired(eID);

}
