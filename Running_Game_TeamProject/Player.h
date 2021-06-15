#ifndef __Player_H_
#define __Player_H_




#include "Obj.h"
class CPlayer :
	public CObj
{
private:
	explicit CPlayer(void);
public:
	virtual ~CPlayer(void);

<<<<<<< HEAD
private:
=======

private:/*
>>>>>>> parent of 76bc780 (Merge branch 'main' into YL)
	enum PLAYER_STATE
	{
		NORMAL, DASHING, JUMPING, 
	};*/


public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;


public:
	virtual void				Moving_Logic(void);


public:
	static CPlayer*		Create(void);


};

#endif // !__Player_H_
