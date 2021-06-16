#ifndef __Struct_H_
#define __Struct_H_

typedef struct tagInfo
{

	tagInfo(void) {}
	tagInfo(const _vec3& vecPos,
		const _vec3& vecSize,
		const float& MoveSpeed = 0.f,
		const float& RotSpeed = 0.f,
		const float& Angle = 0.f) :vPos(vecPos), vSize(vecSize), fMoveSpeed(MoveSpeed), fRotSpeed(RotSpeed), fAngle(Angle) {}

	// �߾Ӱ�, �̹��� ������, ũ��(Scale��), �̵����ǵ�, ȸ�����ǵ�, ȸ���ޱ۰�, RGBA��
	_vec3		vPos;
	_vec3		vSize;
	_vec3		vScale;
	_vec3		vPoint[4];
	_vec3		vDraw[4];
	D3DXCOLOR	vColor;
	float		fMoveSpeed;
	float		fRotSpeed;
	float		fAngle;

	// ü��
	float			fHP;
	float			fMaxHP;


}INFO;


typedef struct tagLineInfo
{
	PDIRECT3DTEXTURE9 pTexture;
	D3DXVECTOR3 vPos;
	D3DXVECTOR2 LPos, RPos;
}LINEINFO;


typedef struct tagTexInfo
{
	D3DXIMAGE_INFO		tImageInfo;
	LPDIRECT3DTEXTURE9	pTexture;

}TEXINFO;


typedef struct tagFrame
{
	float  fStartFrame;
	float  fMaxFrame;
	float  fFrameSpeed;


	wstring wstrObjKey;
	wstring wstrStateKey;
}FRAME;


typedef struct tagTime
{
	DWORD		dwCountTime;
	DWORD		dwEndTime;

}CUSTOMTIME;

typedef struct tagTile
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	bool bCollide;


	bool bPlayerCol;
	_vec3 vScale;

	BYTE byDrawID;
	BYTE byOption;
}TILE;


#endif __Struct_H_