#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"


IMPLEMENT_SINGLETON(CSubject);
CSubject::CSubject()
{
}


CSubject::~CSubject()
{
	for (auto& pObserver : m_listObserver)
		Safe_Delete(pObserver);

	m_listObserver.clear();
}

void CSubject::Subscribe(CObserver * pObserver)
{
	NULL_CHECK_RETURN(pObserver, );

	m_listObserver.emplace_back(pObserver);

}

void CSubject::UnSubscribe(CObserver * pObserver)
{
	 auto& iter_find = find(m_listObserver.begin(), m_listObserver.end(), pObserver);

	if (m_listObserver.end() == iter_find)
		return;

	Safe_Delete(*iter_find);

	m_listObserver.erase(iter_find);

}

void CSubject::Notify(int iMessage, void * pData)
{
	for (CObserver* pObserver : m_listObserver)
		pObserver->Update(iMessage, pData);
}
