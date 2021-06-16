#include "stdafx.h"
#include "PlayerObserver.h"


CPlayerObserver::CPlayerObserver()
	:m_fHp(0.f),
	m_iCoin(0),
	m_iJelly(0)
{
}


CPlayerObserver::~CPlayerObserver()
{
}

void CPlayerObserver::Update(int iMessage, void * pData)
{
	switch (iMessage)
	{
	case DATA_MESSAGE::HP:
		m_fHp = *static_cast<float*>(pData);
		break;
	case DATA_MESSAGE::COIN:
		m_iCoin += *static_cast<int*>(pData);
		break;
	case DATA_MESSAGE::JELLY:
		m_iJelly += *static_cast<int*>(pData);
		break;
	}

}

CPlayerObserver * CPlayerObserver::Create(void)
{
	CPlayerObserver*		pInstance = new CPlayerObserver;

	return pInstance;
}
