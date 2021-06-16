#ifndef __PlayerObserver_H_
#define __PlayerObserver_H_



#include "Observer.h"
class CPlayerObserver :public CObserver
{
private:
	explicit CPlayerObserver(void);

public:
	virtual ~CPlayerObserver(void);

public:
	float	Get_PlayerHP(void) { return m_fHp; }
	int		Get_PlayerJelly(void) { return m_iJelly; }
	int		Get_PlayerCoin(void) { return m_iCoin; }

public:
	// CObserver을(를) 통해 상속됨
	virtual void Update(int iMessage, void * pData) override;

public:
	static CPlayerObserver*		Create(void);


private:
	float		m_fHp;
	int			m_iJelly;
	int			m_iCoin;
};


#endif // !__PlayerObserver_H_
