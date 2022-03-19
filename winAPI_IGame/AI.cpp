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

CState* AI::GetState(MON_STATE state)
{
	map<MON_STATE, CState*>::iterator iter = m_mapState.find(state);

	if (m_mapState.end() == iter)
		return nullptr;

	return iter->second;
}

void AI::SetCurState(MON_STATE state)
{
	m_pCurState = GetState(state);
	assert(m_pCurState);
}

void AI::AddState(CState* state)
{
	CState* pState = GetState(state->GetType());
	assert(!pState);

	m_mapState.insert(make_pair(state->GetType(), state));
	state->m_pOwnerAI = this;
}


