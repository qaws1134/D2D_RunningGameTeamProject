#ifndef __HealthIcon_H_
#define __HealthIcon_H_


#include "Obj.h"
class CHealthIcon :public CObj
{
private:
	explicit CHealthIcon(void);
public:
	virtual ~CHealthIcon(void);

	// CObj을(를) 통해 상속됨
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;




private:
	virtual void Moving_Logic(void) override;


public:
	static CHealthIcon*		Create();
};

#endif // !__HealthIcon_H_
