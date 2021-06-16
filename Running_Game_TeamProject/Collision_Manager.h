#ifndef __Colision_Manager
#define __Colision_Manager



class CObj;
class CCollision_Manager
{
public:
	explicit CCollision_Manager();
	virtual ~CCollision_Manager();

public:
	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_Monster(list<CObj*>& _Dst, list<CObj*>& _Src,int _damage);
	static void Collision_Rect(CObj* pPlayer, list<CObj*>& listItem);
	static void Collision_Monster(CObj * pPlayer, list<CObj*>& _Src);
	
	//static void Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src);

	static bool Check_Sphere(CObj* _pDst, CObj* _pSrc);
	static bool Check_Rect(CObj* _pDst, CObj* _pSrc, float* _x, float* _y);



};


#endif // !__Colision_Manager
