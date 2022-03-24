#include "framework.h"
#include "CStage02.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CMonster.h"
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


}

void CStage02::Exit()
{
	DeleteAll();
}
