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
	const FRAME&	Get_Frame(void) { return m_tFrame; }


	// Set
	// 최초 위치값 설정
	virtual void	Set_Pos(const _vec3& vPos) { m_tInfo.vPos = vPos; }
	void			Set_Dead(void) { m_bDead = true; }
	void			Set_Collied(void) { m_bIsCollied = true; }
	void			Set_Size(const _vec3& vSize) { m_tInfo.vSize = vSize; }
	void			Set_MatTrans(_mat _mattInfo) { m_matInfo[MATRIXID::TRANS] = _mattInfo; }

public:
	virtual HRESULT		Ready_Object(void)PURE;
	virtual int			Update_Object(void)PURE;
	virtual void		LateUpdate_Object(void)PURE;
	virtual void		Render_Object(void)PURE;
	virtual void		Release_Object(void)PURE;


public:
	HRESULT						Setting_TexInfo(void);
protected:
	virtual void				Moving_Logic(void)PURE;

	// TEXINFO 뽑아오는 함수

	// TEXINFO 뽑아오는 함수

	// 애니메이션 프레임 증가함수
	virtual void				Move_Frame(void);

protected:
	// 사각형
	void	Ready_Rectangle(void);

protected:
	//OBJID			m_eID;
	INFO			m_tInfo;
	bool			m_bDead;
	bool			m_bIsCollied;

	// 현재 그림을 렌더링하기위해 선언한 TEXINFO*
	const TEXINFO*	m_pTexInfo = nullptr;
	FRAME			m_tFrame;
	_mat			m_matInfo[MATRIXID::END];
};


#endif // !__Obj_H_
