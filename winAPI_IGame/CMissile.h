#pragma once
#include "CGameObject.h"

class CMissile : public CGameObject
{
private:
	fVec2 m_fvDir;
	float m_fSpeed = 400.f;

public:
	CMissile();
	~CMissile();
	virtual CMissile* Clone();

	virtual void update();
	virtual void render();

	void SetDir(fVec2 vec);
	void SetDir(float theta);

	virtual void OnCollisionEnter(CCollider* pOther);
};

