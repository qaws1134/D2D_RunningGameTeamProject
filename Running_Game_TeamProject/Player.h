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
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(void) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;
	virtual void Release_Object(void) override;


public:
	virtual void				Moving_Logic(void);
	void						Item_Acquired(const ITEMID::ID& eID);
	void						Key_Input(void);
private:
	void		Switch_State(const PLAYER_STATE& eState);

public:
	static CPlayer*		Create(void);

	PLAYER_STATE		m_eCurState;
	PLAYER_STATE		m_ePreState;

	// ���� ������ ���� ī��Ʈ
	int					m_iCoin;
	int					m_iJelly;

	// ������ ���ѽð���
	CUSTOMTIME			m_GiantTime;
	CUSTOMTIME			m_MagnetTime;
	CUSTOMTIME			m_DashTime;

	// ���� üũ�� �Ұ�
	bool				m_bInvincible;

};

#endif // !__Player_H_
