#pragma once
#include "Obj.h"
class CFieldHurdle :
	public CObj
{
private:
	explicit CFieldHurdle();
public:
	virtual ~CFieldHurdle();

public :
	static CFieldHurdle * Create(_vec3 _vPos, HURDLEID::ID _eID);

	void Set_ID(HURDLEID::ID _eID) { m_eID = _eID; }
	// CObj을(를) 통해 상속됨
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;
	
	virtual void Move_Frame()override;
private:
	HURDLEID::ID m_eID;
	BYTE byDrawID;
	BYTE byOption;



	// CObj을(를) 통해 상속됨
	virtual void Moving_Logic(void) override;

};

