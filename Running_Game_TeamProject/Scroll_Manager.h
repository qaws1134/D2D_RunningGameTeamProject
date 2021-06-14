#pragma once
#ifndef __SCROLL_MANAGER_H__
#define __SCROLL_MANAGER_H__
class CScroll_Manager
{
	DECLARE_SINGLETON(CScroll_Manager)
private:
	explicit CScroll_Manager();
	~CScroll_Manager();
public:
	const _vec3& Get_Scroll(void) { return m_vScroll; }


public:
	void Set_Scroll(_vec3& vScroll) { m_vScroll += vScroll; }


	// æ¿ πŸ≤Ó∏È Ω∫≈©∑— √ ±‚»≠
public:
	void Reset_Scroll(void);
private:
	_vec3 m_vScroll;
	
};

#endif
