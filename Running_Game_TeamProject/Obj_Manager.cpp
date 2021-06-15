#include "stdafx.h"
#include "Obj_Manager.h"
#include "Collision_Manager.h"
#include "SceneMgr.h"
#include "Obj.h"

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
