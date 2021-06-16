#pragma once
#ifndef __MYMENU_H__
#define __MYMENU_H__
#include "Scene.h"
class CMyMenu :
	public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

	// CScene을(를) 통해 상속됨
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void LateUpdate_Scene() override;
	virtual void Render_Scene(void) override;
	virtual void Release_Scene(void) override;

	static CMyMenu*	Create(void);


private:
	_vec3 m_vPos;
	_vec3 m_vSize;
	_vec3 m_vScale;

	_mat m_matScale;
	_mat m_matTrans;
	_mat m_matWorld;

};


#endif // !__MYMENU_H__
