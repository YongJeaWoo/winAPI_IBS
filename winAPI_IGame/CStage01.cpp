#include "framework.h"
#include "CStage01.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CZen.h"
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

	// 몬스터가 다 죽었을 때 씬 전환
	if (GetGroupObject(GROUP_GAMEOBJ::ENEMY).size() == 0)
	{
		ChangeScn(GROUP_SCENE::STAGE_02);
	}
}

void CStage01::Enter()
{
	// 타일 로드
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Stage01.tile";
	LoadTile(path);

	CMap* BackGround = new CMap;
	BackGround->Load(L"BackGround", L"texture\\background\\BackGround.png");
	BackGround->SetPos(fPoint(0.f, 0.f));
	BackGround->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(BackGround, GROUP_GAMEOBJ::BACKGROUND);

	// 배경
	CMap* BG = new CMap;
	BG->Load(L"Stage01", L"texture\\background\\Stage01.png");
	BG->SetPos(fPoint(0.f, 0.f));
	BG->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(BG, GROUP_GAMEOBJ::STAGE_01);

	CPlayer* Bubby = new CPlayer;
	AddObject(Bubby, GROUP_GAMEOBJ::PLAYER);
	Bubby->SetPos(fVec2(150.f, 650.f));
	Bubby->RegisterPlayer();
	
	CZen* ZenChan1 = new CZen;
	ZenChan1->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	AddObject(ZenChan1, GROUP_GAMEOBJ::ENEMY);

	CZen* ZenChan2 = CZen::Create(MON_TYPE::NORMAL, fPoint(300.f, 300.f));
	AddObject(ZenChan2, GROUP_GAMEOBJ::ENEMY);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ENEMY);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE, GROUP_GAMEOBJ::ENEMY);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MISSILE);
}

void CStage01::Exit()
{
	DeleteAll();
}
