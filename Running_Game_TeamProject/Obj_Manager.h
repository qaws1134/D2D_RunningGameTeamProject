#ifndef __CObj_Mgr_H__
#define __CObj_Mgr_H__


class CObj;
class CObj_Manager
{
	DECLARE_SINGLETON(CObj_Manager)

private:
	explicit CObj_Manager();
	virtual ~CObj_Manager();


public:
	HRESULT		Ready_Object(void);
	int			Update_Object(void);
	void		LateUpdate_Object(void);
	void		Render_Object(void);
	void		Release_Object(void);


public:
	list<CObj*>* Get_List(OBJID::ID eID) { return &m_listObj[eID]; }


public:
	HRESULT		Insert_Obj(const OBJID::ID& eID, CObj* pObj);
	void		Item_Acquired(ITEMID::ID eID);


private:
	list<CObj*>	m_listObj[OBJID::END];
};

#endif // !__CObj_Mgr_H__
