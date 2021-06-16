#ifndef __CoinScore_H_
#define __CoinScore_H_



#include "Obj.h"
class CObserver;
class CCoinScore :public CObj
{
private:
	explicit CCoinScore(void);

public:
	virtual ~CCoinScore(void);


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
	static CCoinScore*			Create(void);


private:
	int					m_iCoin;
	CObserver*			m_pObserver;
	TCHAR				m_szBuf[MAX_PATH];

};

#endif // !__CoinScore_H_
