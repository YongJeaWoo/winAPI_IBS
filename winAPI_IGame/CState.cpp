#include "framework.h"
#include "CState.h"
#include "AI.h"
#include "CZen.h"

CState::CState(STATE_MON state)
{
	m_pOwnerAI = nullptr;
	m_eState = state;
}

CState::~CState()
{
}

AI* CState::GetOwnerAI()
{
	return m_pOwnerAI;
}

STATE_MON CState::GetType()
{
	return m_eState;
}

CZen* CState::GetMonster()
{
	return m_pOwnerAI->GetOwnerAI();
}
