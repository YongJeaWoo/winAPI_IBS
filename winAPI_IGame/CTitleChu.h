#pragma once
#include "CGameObject.h"

class CTitleChu : public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	CTitleChu();
	~CTitleChu();

	virtual CTitleChu* Clone();

	virtual void update();
	virtual void render();

	void Load(const wstring& strKey, const wstring& strPath);

	virtual void Dance();
};

