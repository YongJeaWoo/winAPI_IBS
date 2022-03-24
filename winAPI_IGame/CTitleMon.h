#pragma once
#include "CGameObject.h"

class CTitleMon : public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	CTitleMon();
	~CTitleMon();

	virtual CTitleMon* Clone();

	virtual void update();
	virtual void render();

	void Load(const wstring& strKey, const wstring& strPath);

	virtual void Dance();
};