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

	// �߾Ӱ�, ũ��, �̵����ǵ�, ȸ�����ǵ�, ȸ���ޱ۰�
	_vec3		vPos;
	_vec3		vSize;
	_vec3		vPoint[4];
	_vec3		vDraw[4];
	float		fMoveSpeed;
	float		fRotSpeed;
	float		fAngle;

	// ü��
	int			iHP;
	// �ʻ��
	unsigned int			iNuke;
}INFO;


typedef struct tagLineInfo
{
	PDIRECT3DTEXTURE9 pTexture;
	D3DXVECTOR3 vPos;

}LINEINFO;


#endif __Struct_H_