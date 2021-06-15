#pragma once

#ifndef __SCENEMGR_H__
#define __SCENEMGR_H__

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
public:
	enum SCENEID { LOGO, MENU, STAGE, END };

private:
	explicit CSceneMgr(void);
	virtual ~CSceneMgr(void);

public:
	void Update_Scene();
	void LateUpdate_Scene();
	void Render_Scene(void);
	void Release_Scene(void);

public:
	void Scene_Change(SCENEID _eID);

public:
	SCENEID Get_SceneID() { return m_ePreScene; }

private:

	CScene*		m_pScene;

	SCENEID		m_ePreScene;
	SCENEID		m_eCurScene;
};


#endif // !__SCENEMGR_H__
