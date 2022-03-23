#include "framework.h"
#include "CRunState.h"
#include "CPlayer.h"
#include "CMonster.h"

CRunState::CRunState(STATE_MON state) 
	: CState(state)
{
}

CRunState::~CRunState()
{
}

void CRunState::update()
{
	CPlayer* pPlayer = CPlayer::GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();

	if (fLen >= pMonster->GetMonInfo().fRecogRange)
		ChangeAIState(GetOwnerAI(), STATE_MON::IDLE);

	// µµ¸ÁÃÄ
	fPoint pos = pMonster->GetPos();
	pos += fvDiff.Normalize() * -100 * fDT;
	pMonster->SetPos(pos);
}

void CRunState::Enter()
{
}

void CRunState::Exit()
{
}
