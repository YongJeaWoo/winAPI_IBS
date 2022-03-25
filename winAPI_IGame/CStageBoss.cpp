#include "framework.h"
#include "CStageBoss.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CZen.h"
#include "CIdleState.h"
#include "CTraceState.h"

CStageBoss::CStageBoss()
{
}

CStageBoss::~CStageBoss()
{
}

void CStageBoss::update()
{
	CScene::update();

	/*if (GetGroupObject(GROUP_GAMEOBJ::ENEMY).size() == 0)
	{
		ChangeScn(GROUP_SCENE::HAPPYENDING);
	}*/
}

void CStageBoss::Enter()
{
	// 타일 로드
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\StageBoss.tile";
	LoadTile(path);

	CMap* BackGround = new CMap;
	BackGround->Load(L"BackGround", L"texture\\background\\BackGround.png");
	BackGround->SetPos(fPoint(0.f, 0.f));
	BackGround->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(BackGround, GROUP_GAMEOBJ::BACKGROUND);

	CMap* BG = new CMap;
	BG->Load(L"StageBoss", L"texture\\background\\StageBoss.png");
	BG->SetPos(fPoint(0.f, 0.f));
	BG->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(BG, GROUP_GAMEOBJ::STAGE_BOSS);

	CPlayer* Bubby = new CPlayer;
	AddObject(Bubby, GROUP_GAMEOBJ::PLAYER);
	Bubby->RegisterPlayer();

	// 테스트 
	CZen* ZenChan1 = CZen::Create(MON_TYPE::NORMAL, fPoint(300.f, 300.f));
	AddObject(ZenChan1, GROUP_GAMEOBJ::ENEMY);

	CZen* ZenChan2 = CZen::Create(MON_TYPE::NORMAL, fPoint(500.f, 300.f));
	AddObject(ZenChan2, GROUP_GAMEOBJ::ENEMY);
}

void CStageBoss::Exit()
{
	DeleteAll();
}
