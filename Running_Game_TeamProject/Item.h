#ifndef __ITEM_H__
#define __ITEM_H__


#include "Obj.h"
class CItem :
	public CObj
{
private:
	explicit CItem(const ITEMID::ID& eID, const int& iIndex = 0);

public:
	virtual ~CItem(void);

public :
	// CObj을(를) 통해 상속됨
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;



public:
	const ITEMID::ID& Get_ItemID(void) { return m_eItemID; }


private:
	virtual void Moving_Logic(void) override;
public:
	static		CItem*	Create(const ITEMID::ID& eID, const int& iIndex = 0);


private:
	ITEMID::ID			m_eItemID;

	// CObj을(를) 통해 상속됨
};


#endif // !__ITEM_H__
