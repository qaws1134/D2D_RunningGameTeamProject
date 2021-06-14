#pragma once
#include "Obj.h"
class CFieldHurdle :
	public CObj
{
public:
	explicit CFieldHurdle();
	virtual ~CFieldHurdle();

public :
	// CObj을(를) 통해 상속됨
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;
	
private:
	HURDLEID::ID m_eID;


};

