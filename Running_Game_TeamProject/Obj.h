#ifndef __Obj_H_
#define __Obj_H_




class CObj abstract
{
protected:
	explicit CObj(void);
	explicit CObj(const INFO& rInfo);
	explicit CObj(const CObj& rhs);
public:
	virtual ~CObj(void);



public:
	enum MATRIXID
	{
		SCALE, ROTATION, TRANS, REV, PARENT, WORLD, END
	};


public:
	// Get
	const INFO&		Get_Info(void) { return m_tInfo; }
	//const OBJID&	Get_ObjID(void) { return m_eID; }
	const bool&		Get_Dead(void) { return m_bDead; }
	// Set
	// ���� ��ġ�� ����
	virtual void	Set_Pos(const _vec3& vPos) { m_tInfo.vPos = vPos; }
	void			Set_Dead(void) { m_bDead = true; }
	void			Set_Collied(void) { m_bIsCollied = true; }


public:
	virtual HRESULT		Ready_Object(void)PURE;
	virtual int			Update_Object(void)PURE;
	virtual void		LateUpdate_Object(void)PURE;
	virtual void		Render_Object(void)PURE;
	virtual void		Release_Object(void)PURE;



protected:
	virtual void				Moving_Logic(void)PURE;

	// TEXINFO �̾ƿ��� �Լ�
	HRESULT						Setting_TexInfo(void);

	// �ִϸ��̼� ������ �����Լ�
	void						Move_Frame(void);


protected:
	// �簢��
	void	Ready_Rectangle(void);

protected:
	//OBJID			m_eID;
	INFO			m_tInfo;
	bool			m_bDead;
	bool			m_bIsCollied;

	// ���� �׸��� �������ϱ����� ������ TEXINFO*
	const TEXINFO*	m_pTexInfo;
	FRAME			m_tFrame;

	_mat			m_matInfo[MATRIXID::END];


};


#endif // !__Obj_H_
