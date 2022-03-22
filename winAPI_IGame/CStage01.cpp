#include "framework.h"
#include "CStage01.h"
#include "CBackGround.h"
#include "CPlayer.h"
#include "CMonster.h"

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

void CStage01::render()
{
}

void CStage01::Enter()
{
	// ���� ���
	CBackGround* BG1 = new CBackGround;
	BG1->Load(L"Stage01", L"texture\\background\\Stage01.png");
	BG1->SetPos(fPoint(0.f, 0.f));
	BG1->SetScale(fPoint(WINSIZEX, WINSIZEY));
	AddObject(BG1, GROUP_GAMEOBJ::STAGE_01);

	CPlayer* Bubby = new CPlayer;
	AddObject(Bubby, GROUP_GAMEOBJ::PLAYER);
	
	CMonster* ZenChan = new CMonster;
	ZenChan->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	AddObject(ZenChan, GROUP_GAMEOBJ::ENEMY);
}

void CStage01::Exit()
{
	DeleteAll();
}
