#include "framework.h"
#include "CState.h"

CState::CState(MON_STATE state)
{
	m_pOwnerAI = nullptr;
	m_eState = state;
}

CState::~CState()
{
}

AI* CState::GetOwner()
{
	return m_pOwnerAI;
}

MON_STATE CState::GetType()
{
	return m_eState;
}
