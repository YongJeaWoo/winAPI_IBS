#pragma once
#include "CGameObject.h"

class CTitleMig : public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	CTitleMig();
	~CTitleMig();

	virtual CTitleMig* Clone();

	virtual void update();
	virtual void render();

	void Load(const wstring& strKey, const wstring& strPath);

	virtual void Dance();
};

