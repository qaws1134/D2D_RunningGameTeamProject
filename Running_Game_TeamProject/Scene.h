#pragma once

#ifndef __SCENE_H__
#define __SCENE_H__

class CScene
{
public:
	explicit CScene();
	virtual ~CScene();

public:
	virtual HRESULT Ready_Scene() PURE;
	virtual void Update_Scene() PURE;
	virtual void LateUpdate_Scene() PURE;
	virtual void Render_Scene(void) PURE;
	virtual void Release_Scene(void)PURE;
};

#endif // !__SCENE_H__
