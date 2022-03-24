#include "framework.h"
#include "CHappyEnding.h"
#include "CBackGround.h"

CHappyEnding::CHappyEnding()
{
}

CHappyEnding::~CHappyEnding()
{
}

void CHappyEnding::update()
{
	CScene::update();
}

void CHappyEnding::Enter()
{
	
}

void CHappyEnding::Exit()
{
	DeleteAll();
}
