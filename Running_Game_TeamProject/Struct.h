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

	// 중앙값, 이미지 사이즈, 크기(Scale값), 이동스피드, 회전스피드, 회전앵글값, RGBA값
	_vec3		vPos;
	_vec3		vSize;
	_vec3		vScale;
	_vec3		vPoint[4];
	_vec3		vDraw[4];
	D3DXCOLOR	vColor;
	float		fMoveSpeed;
	float		fRotSpeed;
	float		fAngle;

	// 체력
	int			iHP;



}INFO;


typedef struct tagLineInfo
{
	PDIRECT3DTEXTURE9 pTexture;
	D3DXVECTOR3 vPos;

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

#endif __Struct_H_