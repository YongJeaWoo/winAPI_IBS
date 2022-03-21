#include "framework.h"
#include "CBackGround.h"
#include "CStage01.h"
#include "CPlayer.h"
#include "CMonster.h"

CStage01::CStage01()
{
	pObj = nullptr;
	mObj = nullptr;
}

CStage01::~CStage01()
{
}

void CStage01::update()
{
	CScene::update();
}

void CStage01::render()
{
}

void CStage01::Enter()
{
	// 메인 타이틀
	CBackGround* StageOneScene = new CBackGround;
	StageOneScene->Load(L"Stage01", L"texture\\background\\Stage01.png");
	StageOneScene->SetPos(fPoint(0, 0));
	StageOneScene->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(StageOneScene, GROUP_GAMEOBJ::STAGE_01);

	CPlayer* Bubby = new CPlayer;
	AddObject(Bubby, GROUP_GAMEOBJ::PLAYER);
	
	CMonster* ZenChan = new CMonster;
	AddObject(ZenChan, GROUP_GAMEOBJ::ENEMY);

}

void CStage01::Exit()
{
	DeleteAll();
}
