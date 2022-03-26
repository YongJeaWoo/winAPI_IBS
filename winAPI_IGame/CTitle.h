#pragma once
#include "CScene.h"
#include "CTitlePlayer.h"
#include "CTitleZen.h"
#include "CTitleChu.h"
#include "CTitleMig.h"
#include "CTitleMon.h"

class CImageObject;

class CTitle : public CScene
{
private:
	bool m_bIsRaise;
	CImageObject*	Iobj;
	CTitlePlayer*	Pobj;
	CTitleZen*		Zobj;
	CTitleChu*		Cobj;
	CTitleMig*		Migobj;
	CTitleMon*		Monobj;

	float m_fAccTime;
	bool m_bIsFadeOut;
	int step = 0;			// 커튼 올라가는 단계

public:
	CTitle();
	virtual ~CTitle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};