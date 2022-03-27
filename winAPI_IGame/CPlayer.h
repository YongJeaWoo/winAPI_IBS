#pragma once
#include "CGameObject.h"

class CD2DImage;

struct PlayerAct
{
	float m_fVelocity;
	bool m_bIsLeft;
	float m_fDelay;

	float m_fSpeed = 300.f;
	float m_fHorizontalSpeed;

	// ���� �����غ���
	float m_fGravity;
	float m_fUpforce;
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;

	UINT m_uiGround;
	UINT m_uiWall;

	PlayerAct act;

	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();

	void update_act();
	void update_ani();

	void RegisterPlayer();
	static CPlayer* GetPlayer();		// ���� �� �ϳ��� �ִ� �÷��̾� ��ü Ȯ�� - ���� �̱��� ����

	virtual void OnCollision(CCollider* _other);
	virtual void OnCollisionEnter(CCollider* _other);
	virtual void OnCollisionExit(CCollider* _other);
};

