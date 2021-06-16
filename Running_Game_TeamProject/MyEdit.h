#pragma once
#ifndef __MYEDIT_H__
#define __MYEDIT_H__

#include "Scene.h"
class CTerrain;
class CMyEdit :
	public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

	// CScene을(를) 통해 상속됨
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void LateUpdate_Scene() override;
	virtual void Render_Scene(void) override;
	virtual void Release_Scene(void) override;

	static CMyEdit* Create();


private:
	CTerrain* m_pTerrain;
	int m_iID;
	bool m_bSwapLine_Or_Hurdle;



};


#endif // !MYEDIT_H__
