#pragma once
#ifndef __TERRAIN_H__
#define __TERRAIN_H__
class CObj;
class CTerrain
{
public:
	explicit CTerrain();
	~CTerrain();

public:
	HRESULT Ready_Terrain();
	void Render_Terrain();
	void Release_Terrain();


public :
	vector<TILE*> Get_Tile() {return m_vecTile;}
public :
	void Set_Tile(int _iID);

public:
	void TilePicking_Terrain(const D3DXVECTOR3& vMousePos, const BYTE& byOption );
	
public :
	void Save_Terrain();
	void Load_Terrain();

private:
	vector<TILE*> m_vecTile;
	FRAME m_tFrame;
	float m_fOffsetY;
	float m_fIncrese;
	_vec3 vFlyDir;
	float m_fAngle;
	HURDLEID::ID m_eID;
	bool bCollide;
};


#endif // !__TERRAIN_H__
