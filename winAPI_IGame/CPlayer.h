#pragma once
#include "CGameObject.h"

class CD2DImage;

enum class CharacterState
{
	IDLE,
	HIT,
	DEAD,

	MOVE,
	ATTACK,
	JUMP,
	FALL,
	BUBBLE,
	JUMPBUBBLE,
	FALLBUBBLE,

	SIZE
};

struct PlayerState
{
	float CurHp;
	float FullHp;

	fVec2 CurDir;
	fVec2 PrevDir;
	float Speed;
	float AccelGravity;
	float Upper;

	bool Jumping;
	bool Acting;
	bool Attacking;
	bool Grounding;

	bool JustHit;
	bool IsRight;
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;

	float m_gravity;

	UINT m_GtileCount;
	UINT m_WtileCount;
	UINT m_PtileCount;

	fPoint m_fCurDir;
	fPoint m_fPrevDir;

	PlayerState pState;

	CharacterState m_State;
	CharacterState m_PrevState;

	void CreateMissile();
	void Jump();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();

	void update_move();
	void update_state();
	void update_animation();

	void RegisterPlayer();

	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);

	static CPlayer* GetPlayer();		// 게임 내 하나만 있는 플레이어 객체 확인(임의 싱글톤 선언)
};

