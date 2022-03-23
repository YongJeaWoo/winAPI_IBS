#include "framework.h"
#include "CTraceState.h"
#include "CPlayer.h"
#include "CMonster.h"

CTraceState::CTraceState(STATE_MON state) : CState(state)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	CPlayer* pPlayer = CPlayer::GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();

	if (pMonster->GetMonInfo().fHp < 20.f && fLen < pMonster->GetMonInfo().fRecogRange)
		ChangeAIState(GetOwnerAI(), STATE_MON::RUN);

	else if (fLen < pMonster->GetMonInfo().fRecogRange)
		ChangeAIState(GetOwnerAI(), STATE_MON::IDLE);

	// ÃßÀûÇØ
	fPoint pos = pMonster->GetPos();
	pos += fvDiff.Normalize() * 100 * fDT;
	pMonster->SetPos(pos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
