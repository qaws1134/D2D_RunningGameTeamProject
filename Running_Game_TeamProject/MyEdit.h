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

	// CScene��(��) ���� ��ӵ�
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


	// ������

	// �ʿ��Ѱ�
	// ��ġ��, ������ID, ������ iCount����
	CObj*			m_pItem;
	ITEMID::ID		m_eItemID;
	int				m_iItemIndex;
	_vec3			m_vItemPos;

	list<CObj*>		m_listItem;

};


#endif // !MYEDIT_H__
