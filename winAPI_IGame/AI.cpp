#include "framework.h"
#include "AI.h"
#include "CState.h"

AI::AI()
{
	m_pOwner = nullptr;
	m_pCurState = nullptr;
}

AI::~AI()
{
	for (map<MON_STATE, CState*>::iterator iter = m_mapState.begin(); iter != m_mapState.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapState.clear();
}

void AI::update()
{
	m_pCurState->update();
}

void AI::AddState(CState* pState)
{
}
