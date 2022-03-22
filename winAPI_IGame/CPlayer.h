#pragma once
#include "CGameObject.h"

class CD2DImage;

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	ATTACK,
	JUMP,
	DEAD,

	SIZE,
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;
	float m_fSpeed = 500;

	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();

	void RegisterPlayer();
	static CPlayer* GetPlayer();		// 게임 내 하나만 있는 플레이어 객체 확인 - 임의 싱글톤 선언
};

