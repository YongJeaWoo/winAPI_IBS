#pragma once
#include "CScene.h"
#include "CDummyTitle.h"

class CImageObject;

class CTitle : public CScene
{
private:
	bool m_bIsRaise;
	CImageObject*	Iobj;
	CDummyTitle*	Pobj;
	float m_fAccTime;
	bool m_bIsFadeOut;

public:
	CTitle();
	virtual ~CTitle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};