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
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;

public:
	void		Item_Acquired(const ITEMID::ID& eItemID);
	



private:
	// Update�� �Լ�
	virtual void				Moving_Logic(void);
	void						Key_Input(void);
	void						Jumping(void);
	void						Item_EffectCheck(void);
	void						Notify_Observer(void);

	// LateUpdate�� �Լ�
	void						Item_Expired_Check(void);
	void						LateUpdate_StateCheck(void);


	void						Switch_State(const PLAYER_STATE& eState);
public:
	static CPlayer*		Create(void);

	PLAYER_STATE		m_eCurState;
	PLAYER_STATE		m_ePreState;




	// ������ bool��
	bool				m_bInvinsible;



	// ��ȭ ������ ���ѽð� ����ü
	CUSTOMTIME			m_tDashTime;
	CUSTOMTIME			m_tGiantTime;
	CUSTOMTIME			m_tMagnetTime;


	// ����� ������ ������ 3�� ��� ���� �ð�
	CUSTOMTIME			m_tDeathTime;
	bool				m_bDeathCountStart;

	// �Ŵ�ȭ ����Ʈ��
	_vec3				m_vLimitScale;
	_vec3				m_vScaleIncrease;
	bool				m_bGiantOn;

	// �뽬 �Ұ�
	bool				m_bDash;


	// ���� ���� ������
	// ���� üũ�� �Ұ�
	bool				m_bJump;
	bool				m_bDoubleJump;
	float				m_fJumpPower;
	float				m_fJumpTime;



	// �÷��̾� ����, ����
	int					m_iCoin;
	int					m_iJelly;
	float				m_fHPMinus;
};

#endif // !__Player_H_
