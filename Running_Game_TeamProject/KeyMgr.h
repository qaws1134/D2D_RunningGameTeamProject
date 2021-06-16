
#ifndef __KEYMGR_H__
#define __KEYMGR_H__

#define VK_MAX 0xFF

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool Key_Pressing(int _key);
	bool Key_Down(int _key);
	bool Key_Up(int _key);


private:
	bool	m_bKeyState[VK_MAX];
};


#endif // !__KEYMGR_H__
