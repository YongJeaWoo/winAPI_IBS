#include "framework.h"
#include "CStage02.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CZen.h"
#include "CTraceState.h"
#include "CIdleState.h"

CStage02::CStage02()
{
}

CStage02::~CStage02()
{
}

void CStage02::update()
{
	CScene::update();

	if (GetGroupObject(GROUP_GAMEOBJ::ENEMY).size() == 0)
	{
		ChangeScn(GROUP_SCENE::STAGE_BOSS);
	}
}

void CStage02::Enter()
{
	CMap* BackGround = new CMap;
	BackGround->Load(L"BackGround", L"texture\\background\\BackGround.png");
	BackGround->SetPos(fPoint(0.f, 0.f));
	BackGround->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(BackGround, GROUP_GAMEOBJ::BACKGROUND);

	CMap* BG = new CMap;
	BG->Load(L"Stage02", L"texture\\background\\Stage02.png");
	BG->SetPos(fPoint(0.f, 0.f));
	BG->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(BG, GROUP_GAMEOBJ::STAGE_02);

	CPlayer* Bubby = new CPlayer;
	AddObject(Bubby, GROUP_GAMEOBJ::PLAYER);
	Bubby->RegisterPlayer();

	CZen* ZenChan1 = CZen::Create(MON_TYPE::NORMAL, fPoint(300.f, 300.f));
	AddObject(ZenChan1, GROUP_GAMEOBJ::ENEMY);

	CZen* ZenChan2 = CZen::Create(MON_TYPE::NORMAL, fPoint(500.f, 300.f));
	AddObject(ZenChan2, GROUP_GAMEOBJ::ENEMY);
}

void CStage02::Exit()
{
	DeleteAll();
}
