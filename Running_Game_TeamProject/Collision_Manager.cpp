#include "stdafx.h"
#include "Collision_Manager.h"
#include "Obj.h"

CCollision_Manager::CCollision_Manager()
{
}

CCollision_Manager::~CCollision_Manager()
{
}



//void CCollision_Manager::Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src)
//{
//	for (auto& Dst : _Dst)
//	{
//		for (auto& Src : _Src)
//		{
//			float fX = 0.f, fY = 0.f;
//			if (Check_Rect(Dst, Src, &fX, &fY))
//			{
//				if (fX > fY)	// 상하 충돌
//				{
//					if (Dst->Get_Info().fY < Src->Get_Info().fY)
//						Src->Set_Pos_Y(fY);
//					else
//						Src->Set_Pos_Y(-fY);
//				}
//				else 			// 좌우 충돌
//				{
//					if (Dst->Get_Info().fX < Src->Get_Info().fX)
//						Src->Set_Pos_X(fX);
//					else
//						Src->Set_Pos_X(-fX);
//				}
//			}
//		}
//	}
//}

void CCollision_Manager::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	float fX = 0.f, fY = 0.f;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{

		}
	}
}

void CCollision_Manager::Collision_Rect_Monster(list<CObj*>& _Dst, list<CObj*>& _Src, int _damage)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			float fX = 0.f, fY = 0.f;
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
			}

		}
	}
}

void CCollision_Manager::Collision_Rect_Obstacle(list<CObj*>& _Dst, vector<TILE*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			float fX = 0.f, fY = 0.f;
			if (Check_Rect_Obstacle(Dst, Src))
			{
				//플레이어 데미지
			}
		}
	}
}


void CCollision_Manager::Collision_Rect(CObj * pPlayer, list<CObj*>& listItem)
{
	/*if (CPlayer::PLAYER_DEAD == static_cast<CPlayer*>(pPlayer)->Get_State() || CPlayer::PLAYER_COMPLETELYDEAD == static_cast<CPlayer*>(pPlayer)->Get_State())
		return;*/

	for (auto& Src : listItem)
	{
		float fX = 0.f, fY = 0.f;
		if (Check_Rect(pPlayer, Src, &fX, &fY))
		{
			Src->Set_Collied();
		}
	}
	
}

void CCollision_Manager::Collision_Monster(CObj * pPlayer, list<CObj*>& _Src)
{
	//if (CPlayer::PLAYER_DEAD == static_cast<CPlayer*>(pPlayer)->Get_State() || CPlayer::PLAYER_COMPLETELYDEAD == static_cast<CPlayer*>(pPlayer)->Get_State() ||
	//	CPlayer::PLAYER_RESURRECTION == static_cast<CPlayer*>(pPlayer)->Get_State())
	//	return;

	//for (auto& Src : _Src)
	//{
	//	float fX = 0.f, fY = 0.f;
	//	if (Check_Rect(pPlayer, Src, &fX, &fY))
	//	{
	//		/*Src->Set_Dead();
	//		Dst->Set_Dead();*/
	//		pPlayer->Set_Collied();

	//		if (OBJ_BOSS == Src->Get_ObjID())
	//			break;
	//		else
	//			Src->Set_Collied();
	//	}
	//}
	//
}


void CCollision_Manager::Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollision_Manager::Check_Sphere(CObj * _pDst, CObj * _pSrc)
{
	float fX = abs(_pDst->Get_Info().vPos.x - _pSrc->Get_Info().vPos.x);
	float fY = abs(_pDst->Get_Info().vPos.y - _pSrc->Get_Info().vPos.y);
	float fDis = sqrtf(fX * fX + fY * fY);

	float fRad = (float)(((_pDst->Get_Info().vSize.x * 0.5f) + (_pSrc->Get_Info().vSize.x * 0.5f)));

	return fDis <= fRad;
}

bool CCollision_Manager::Check_Rect(CObj * _pDst, CObj * _pSrc, float * _x, float * _y)
{
	// 중점간의 거리
	float fX = abs(_pDst->Get_Info().vPos.x - _pSrc->Get_Info().vPos.x);
	float fY = abs(_pDst->Get_Info().vPos.y - _pSrc->Get_Info().vPos.y);
	

	// 반지름 합
	float fCX = ((_pDst->Get_Info().vSize.x + _pSrc->Get_Info().vSize.x) * 0.5f);
	float fCY = ((_pDst->Get_Info().vSize.y + _pSrc->Get_Info().vSize.y) * 0.5f);

	if (fCX > fX && fCY > fY)
	{
		*_x = fCX - fX;
		*_y = fCY - fY;
		return true;
	}
	return false;
}

bool CCollision_Manager::Check_Rect_Obstacle(CObj * _pDst, TILE * _pSrc)
{
	if (!_pSrc->bCollide)
		return false;

	// 중점간의 거리
	float fX = abs(_pDst->Get_Info().vPos.x - _pSrc->vPos.x);
	float fY = abs(_pDst->Get_Info().vPos.y - _pSrc->vPos.y);


	// 반지름 합
	float fCX = ((_pDst->Get_Info().vSize.x + _pSrc->vSize.x) * 0.5f);
	float fCY = ((_pDst->Get_Info().vSize.y + _pSrc->vSize.y) * 0.5f);

	if (fCX > fX && fCY > fY)
	{
		return true;
	}
	return false;
}
