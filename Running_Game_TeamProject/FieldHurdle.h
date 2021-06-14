#pragma once
#include "Obj.h"
class CFieldHurdle :
	public CObj
{
public:
	explicit CFieldHurdle();
	virtual ~CFieldHurdle();

public :
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;
	
private:
	HURDLEID::ID m_eID;


};

