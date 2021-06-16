#ifndef __HealthBar_H_
#define __HealthBar_H_



#include "Obj.h"

class CObserver;
class CHealthBar : public CObj
{
private:
	explicit CHealthBar(void);
public:
	virtual ~CHealthBar(void);


public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Ready_Object(void) override;
	virtual int		Update_Object(void) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;
	virtual void	Release_Object(void) override;
	
	
	
private:
	virtual void Moving_Logic(void) override;



public:
	static CHealthBar*		Create(void);


private:
	// �÷��̾��� ü�°�
	float				m_fHealth;
	float				m_fMaxHealth;
	CObserver*			m_pObserver;
};

#endif // !__HealthBar_H_
