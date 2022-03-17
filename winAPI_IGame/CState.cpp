#include "framework.h"
#include "CState.h"

CState::CState(MON_STATE state)
{
}

CState::~CState()
{
}

AI* CState::GetOwner()
{
	return m_pOwnerAi;
}