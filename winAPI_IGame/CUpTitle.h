#pragma once
#include "CGameObject.h"

class CUpTitle : public CGameObject
{
private:
	fVec2 m_fvDir;
	float m_fSpeed = 300.f;

public:
	CUpTitle();
	~CUpTitle();
	virtual CUpTitle* clone();

	virtual void update();
	virtual void render();

	void SetDir(fVec2 vec);
};

