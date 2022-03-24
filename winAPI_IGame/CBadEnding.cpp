#include "framework.h"
#include "CBadEnding.h"

CBadEnding::CBadEnding()
{
}

CBadEnding::~CBadEnding()
{
}

void CBadEnding::update()
{
	CScene::update();
}

void CBadEnding::Enter()
{

}

void CBadEnding::Exit()
{
	DeleteAll();
}
