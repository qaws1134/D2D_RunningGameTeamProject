#pragma once

#ifndef __LINEMGR_H__
#define __LINEMGR_H__

class CLine;
class CLineMgr
{
	DECLARE_SINGLETON(CLineMgr)
private:
	explicit CLineMgr();
	~CLineMgr();

public:
	void Initialize();
	void Render();
	void Release();

public:
	bool Collision_Line(float _x, float* _y);
	void Set_End() { m_bEnd = !m_bEnd; };
	void Back_Line() { m_listLine.pop_back(); }
	void Picking_Line();
	void Save_Line();
	void Load_Line();

private:
	list<CLine*>	m_listLine;
	bool m_bCheck;
	bool m_bEnd;
	_vec2 m_tLinePos[2];

};


#endif // !__LINEMGR_H__

