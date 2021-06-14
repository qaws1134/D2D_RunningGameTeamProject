#include "stdafx.h"
#include "FieldHurdle.h"


CFieldHurdle::CFieldHurdle()
{
}


CFieldHurdle::~CFieldHurdle()
{
}

HRESULT CFieldHurdle::Ready_Object(void)
{
	switch (m_eID)
	{
	case HURDLEID::FLOOR:

		break;
	case HURDLEID::FLOOR2F:
		break;
	case HURDLEID::LOWHILL:
		break;
	case HURDLEID::HIGHHILL:
		break;
	case HURDLEID::BULLET:
		break;
	default:
		break;
	}

	return S_OK;
}

int CFieldHurdle::Update_Object(void)
{
	return 0;
}

void CFieldHurdle::LateUpdate_Object(void)
{
}

void CFieldHurdle::Render_Object(void)
{
}

void CFieldHurdle::Release_Object(void)
{
}
