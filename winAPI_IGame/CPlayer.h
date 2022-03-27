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
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;

	UINT m_uiGroundCount;
	UINT m_uiWallCount;

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
	static CPlayer* GetPlayer();		// 게임 내 하나만 있는 플레이어 객체 확인 - 임의 싱글톤 선언

	virtual void OnCollision(CCollider* _other);
	virtual void OnCollisionEnter(CCollider* _other);
	virtual void OnCollisionExit(CCollider* _other);
};

