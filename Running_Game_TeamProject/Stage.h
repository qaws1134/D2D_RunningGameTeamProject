#ifndef __Stage_H_
#define __Stage_H_


#include "Scene.h"
class CStage :
	public CScene
{
private:
	explicit CStage(void);
public:
	virtual ~CStage(void);

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void LateUpdate_Scene() override;
	virtual void Render_Scene(void) override;
	virtual void Release_Scene(void) override;


public:
	static CStage*		Create(void);
};

#endif // !__Stage_H_
