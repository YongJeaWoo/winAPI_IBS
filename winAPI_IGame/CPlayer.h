#pragma once
#include "CGameObject.h"

class CD2DImage;

//enum class PLAYER_STATE
//{
//	IDLE,
//	WALK,
//	ATTACK,
//	JUMP,
//	DEAD,
//
//	SIZE,
//};

struct PlayerAct
{
	float m_fVelocity;
	bool m_bIsLeft;
	float m_fDelay;
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;
	float m_fSpeed = 500;
	float m_fHorizontalSpeed;

	UINT m_uiGroundCount;

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

