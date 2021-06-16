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
		RUN, DASHING, JUMPING, DOUBLEJUMPING,  SLIDING, HIT, DEAD, END
	};




public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;

public:
	void		Item_Acquired(const ITEMID::ID& eItemID);
	



private:
	// Update용 함수
	virtual void				Moving_Logic(void);
	void						Key_Input(void);
	void						Jumping(void);
	void						Item_EffectCheck(void);
	void						Notify_Observer(void);

	// LateUpdate용 함수
	void						Item_Expired_Check(void);
	void						LateUpdate_StateCheck(void);


	void						Switch_State(const PLAYER_STATE& eState);
public:
	static CPlayer*		Create(void);

	PLAYER_STATE		m_eCurState;
	PLAYER_STATE		m_ePreState;




	// 무적용 bool값
	bool				m_bInvinsible;



	// 강화 아이템 제한시간 구조체
	CUSTOMTIME			m_tDashTime;
	CUSTOMTIME			m_tGiantTime;
	CUSTOMTIME			m_tMagnetTime;


	// 사망시 사망모션 끝나고 3초 재기 위한 시간
	CUSTOMTIME			m_tDeathTime;
	bool				m_bDeathCountStart;

	// 거대화 리미트값
	_vec3				m_vLimitScale;
	_vec3				m_vScaleIncrease;
	bool				m_bGiantOn;

	// 대쉬 불값
	bool				m_bDash;


	// 점프 관련 변수들
	// 점프 체크용 불값
	bool				m_bJump;
	bool				m_bDoubleJump;
	float				m_fJumpPower;
	float				m_fJumpTime;



	// 플레이어 코인, 젤리
	int					m_iCoin;
	int					m_iJelly;
	float				m_fHPMinus;
};

#endif // !__Player_H_
