#ifndef __JellyScore_H_
#define __JellyScore_H_


#include "Obj.h"
class CObserver;
class CJellyScore :
	public CObj
{
private:
	explicit CJellyScore(void);

public:
	virtual ~CJellyScore(void);

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;



private:
	virtual void Moving_Logic(void) override;


public:
	static CJellyScore*			Create(void);

private:
	int					m_iJelly;
	CObserver*			m_pObserver;
	TCHAR				m_szBuf[MAX_PATH];
	int					m_iBufSize;
};

#endif // !__JellyScore_H_
