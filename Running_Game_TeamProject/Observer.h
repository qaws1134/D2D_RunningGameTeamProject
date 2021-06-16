#ifndef __Observer_H_
#define __Observer_H_



class CObserver abstract
{
protected:
	explicit CObserver(void);

public:
	virtual ~CObserver(void);

public:
	virtual void Update(int iMessage, void* pData)PURE;

};

#endif // !__Observer_H_
