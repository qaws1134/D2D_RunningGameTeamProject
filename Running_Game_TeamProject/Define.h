#ifndef __Define_H__
#define __Define_H__

#define WINCX 800
#define WINCY 600
#define WINCX 1000
#define WINCY 830

extern HWND g_hWnd;

#define ERR_MSG(Message) MessageBox(nullptr, Message, L"System Error", MB_OK)



// °´Ã¼ÀÇ Á×À½ ÆÇº° ¸®ÅÏ°ª
#define OBJ_DEAD -1
#define OBJ_NOEVENT 0


#define CREATE(CLASS_NAME)									\
CLASS_NAME* pInstance = new CLASS_NAME;						\
if(FAILED(pInstance->Ready_GameObject()))					\
	Safe_Delete(pInstance);									\
return pInstance;

#define DEAD_CHECK \
if(m_bDead) return OBJ_DEAD;


#define FAILED_CHECK_RETURN(_hr, _return)					\
if(_hr < 0) return _return;								

#define NULL_CHECK_RETURN(_obj, _return)					\
if(nullptr == _obj) return _return;	




#define DECLARE_SINGLETON(CLASSNAME)						\
public:														\
	static CLASSNAME*	Get_Instance(void);					\
	static void			Destroy_Instance(void);				\
															\
private:													\
	static CLASSNAME*	m_pInstance;						\


#define IMPLEMENT_SINGLETON(CLASSNAME)						\
CLASSNAME*	CLASSNAME::Get_Instance(void)					\
{															\
	if (nullptr == m_pInstance)								\
		m_pInstance = new CLASSNAME;						\
	return m_pInstance;										\
}															\
void		CLASSNAME::Destroy_Instance(void)				\
{															\
	if (nullptr != m_pInstance)								\
	{														\
		delete m_pInstance;									\
		m_pInstance = nullptr;								\
	}														\
}															\
CLASSNAME*	CLASSNAME::m_pInstance = nullptr;


#endif // !__Define_H__
