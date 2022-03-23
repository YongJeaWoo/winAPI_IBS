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
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;
	float m_fSpeed = 500;
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
};

