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
	// Get
	const INFO&		Get_Info(void) { return m_tInfo; }
	//const OBJID&	Get_ObjID(void) { return m_eID; }
	const bool&		Get_Dead(void) { return m_bDead; }
	// Set
	// 최초 위치값 설정
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

	// 사각형
	void	Ready_Rectangle(void);

protected:
	INFO			m_tInfo;
	//OBJID			m_eID;
	bool			m_bDead;
	bool			m_bIsCollied;
};


#endif // !__Obj_H_
