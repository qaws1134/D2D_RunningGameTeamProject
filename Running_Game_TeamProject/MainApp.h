#ifndef __MainApp_H_
#define __MainApp_H_


class CMainApp
{
private:
	explicit CMainApp(void);
public:
	virtual ~CMainApp(void);



public:
	HRESULT		Ready_MainApp(void);
	void		Update_MainApp(void);
	void		LateUpdate_MainApp(void);
	void		Render_MainApp(void);
	void		Release_MainApp(void);

public:
	static CMainApp*		Create(void);


private:

};

#endif // !__MainApp_H_
