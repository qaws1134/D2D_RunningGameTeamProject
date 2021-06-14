#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__
#include "Obj.h"
class CItem :
	public CObj
{
public:
	explicit CItem();
	virtual ~CItem();

public :
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;
};


#endif // !__ITEM_H__
