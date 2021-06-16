#ifndef __Subject_H_
#define __Subject_H_

class CObserver;
class CSubject
{
	DECLARE_SINGLETON(CSubject)
private:
	explicit CSubject(void);
	virtual ~CSubject(void);

public:
	void Subscribe(CObserver* pObserver);

	void UnSubscribe(CObserver* pObserver);

	void Notify(int iMessage, void* pData);

private:
	list<CObserver*> m_listObserver;

};

#endif // !__Subject_H_
