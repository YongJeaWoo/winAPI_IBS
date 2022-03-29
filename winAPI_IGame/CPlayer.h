#pragma once
#include "CGameObject.h"

class CD2DImage;

struct PlayerAct
{
	float m_fVelocity;
	bool m_bIsLeft;
	float m_fDelay;

	float m_fSpeed = 300.f;
	float m_YPower;

	bool Jump = false;
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;

	UINT m_GtileCount;
	UINT m_WtileCount;
	UINT m_PtileCount;

	PlayerAct act;

	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();

	void update_action();
	void update_animation();

	void RegisterPlayer();
	static CPlayer* GetPlayer();		// ���� �� �ϳ��� �ִ� �÷��̾� ��ü Ȯ�� - ���� �̱��� ����

	virtual void OnCollision(CCollider* _other);
	virtual void OnCollisionEnter(CCollider* _other);
	virtual void OnCollisionExit(CCollider* _other);
};

