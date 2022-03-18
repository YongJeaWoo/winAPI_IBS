#pragma once
#include "CGameObject.h"
class CTitleGround : public CGameObject
{
private:
	CD2DImage* m_pImg;
	fVec2 m_fvDir;

public:
	CTitleGround();
	virtual ~CTitleGround();

	virtual CTitleGround* Clone();
	virtual void update();
	virtual void render();

	void SetDir(fVec2 vec);

	void Load(wstring strKey, wstring strPath);
};

