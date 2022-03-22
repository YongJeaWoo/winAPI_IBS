#include "framework.h"
#include "CStage01.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTraceState.h"
#include "CIdleState.h"

CStage01::CStage01()
{
}

CStage01::~CStage01()
{
}

void CStage01::update()
{
	CScene::update();
}

void CStage01::Enter()
{
	CMap* BackGround = new CMap;
	BackGround->Load(L"BackGround", L"texture\\background\\BackGround.png");
	BackGround->SetPos(fPoint(0.f, 0.f));
	BackGround->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(BackGround, GROUP_GAMEOBJ::BACKGROUND);

	// ¹è°æ
	CMap* BG1 = new CMap;
	BG1->Load(L"Stage01", L"texture\\background\\Stage01.png");
	BG1->SetPos(fPoint(0.f, 0.f));
	BG1->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(BG1, GROUP_GAMEOBJ::STAGE_01);

	CPlayer* Bubby = new CPlayer;
	AddObject(Bubby, GROUP_GAMEOBJ::PLAYER);
	Bubby->RegisterPlayer();
	
	CMonster* ZenChan1 = new CMonster;
	ZenChan1->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	AddObject(ZenChan1, GROUP_GAMEOBJ::ENEMY);

	CMonster* ZenChan2 = CMonster::Create(MON_TYPE::NORMAL, fPoint(300.f, 300.f));
	AddObject(ZenChan2, GROUP_GAMEOBJ::ENEMY);
}

void CStage01::Exit()
{
	DeleteAll();
}
