#pragma once
#ifndef __MYEDIT_H__
#define __MYEDIT_H__

#include "Scene.h"
class CTerrain;
class CObj;
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
	void		Key_Input(void);
	void		Save_ItemList(void);
	void		Load_ItemList(void);


private:
	CTerrain* m_pTerrain;
	int m_iID;
	bool m_bSwapLine_Or_Hurdle;


	// 아이템

	// 필요한거
	// 위치값, 아이템ID, 젤리는 iCount까지
	CObj*			m_pItem;
	ITEMID::ID		m_eItemID;
	int				m_iItemIndex;
	_vec3			m_vItemPos;

	list<CObj*>		m_listItem;

};


#endif // !MYEDIT_H__
