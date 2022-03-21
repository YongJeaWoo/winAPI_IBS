#pragma once
#include "CGameObject.h"

class CTitle;

class CPlayerTitle : public CGameObject
{
private:
	CD2DImage* m_pImg;
	bool m_bIsRaise;

public:
	CPlayerTitle();
	~CPlayerTitle();

	virtual CPlayerTitle* Clone();

	virtual void update();
	virtual void render();

	void Load(const wstring& strKey, const wstring& strPath);
};