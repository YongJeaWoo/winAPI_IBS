#pragma once

class CGameObject;

class CGravity
{
	friend class CGameObject;

private:
	CGameObject* m_pOwner;
	UINT m_uiCountGround;

public:
	CGravity();
	virtual ~CGravity();

	virtual void update();
	virtual void finalupdate();
};