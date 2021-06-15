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


private:
	enum PLAYER_STATE
	{
		RUN, DASHING, JUMPING, DOUBLEJUMPING, SLIDING, HIT, DEAD, END
	};




public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;


public:
	void						Item_Acquired(const ITEMID::ID& eID);



private:
	virtual void				Moving_Logic(void);
	void						Switch_State(const PLAYER_STATE& eState);
	void						Key_Input(void);
	void						Item_ExpiredTimeCheck(void);

public:
	static CPlayer*		Create(void);

	PLAYER_STATE		m_eCurState;
	PLAYER_STATE		m_ePreState;

	// 점수 젤리와 코인 카운트
	int					m_iCoin;
	int					m_iJelly;

	// 아이템 제한시간값
	CUSTOMTIME			m_tGiantTime;
	CUSTOMTIME			m_tMagnetTime;
	CUSTOMTIME			m_tDashTime;

	// 무적 체크용 불값
	bool				m_bInvincible;

	// 거대화용 불값과 크기제한값
	bool				m_bGiantOn;
	_vec3				m_vLimitedScale;
};

#endif // !__Player_H_
