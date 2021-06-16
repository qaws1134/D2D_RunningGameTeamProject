#pragma once

#ifndef __LINE_H__
#define __LINE_H__

class CLine
{
public:
	CLine();
	CLine(_vec2 LPos, _vec2 RPos) { m_tInfo.LPos = LPos; m_tInfo.RPos = RPos; };
	~CLine();

public:
	void Initialize();
	void Render();
	void Release();

public:
	const LINEINFO& Get_Info() const { return m_tInfo; }

private:
	LINEINFO	m_tInfo;
};


#endif // !__LINE_H__
