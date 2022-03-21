#pragma once

class CGameObject;

class CGravity
{
private:
	friend class CGameObject;

	CGameObject* m_pOwner;
	bool m_bGround;

public:
	CGravity();
	~CGravity();

	virtual void finalupdate();
};

