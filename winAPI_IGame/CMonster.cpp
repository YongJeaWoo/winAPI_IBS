#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CRunState.h"

CMonster::CMonster()
{
	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"MonsterTex", L"texture\\PlayerStand.png");
	m_pAI = nullptr;
	Info = {};

	SetName(L"Monster");
	SetScale(fPoint(100.f, 100.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(90.f, 90.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PlayerStand", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 5, true);
	GetAnimator()->Play(L"PlayerStand");
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}

CMonster* CMonster::Clone()
{
	CMonster* newMonster = new CMonster;
	if (nullptr != m_pAI)
		newMonster->m_pAI = new AI;

	return new CMonster(*newMonster);
}

CMonster* CMonster::Create(MON_TYPE type, fPoint pos)
{
	CMonster* pMon = nullptr;

	switch (type)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);

		sMonInfo info = {};
		// info.fAtt = 10.f;
		info.fRecogRange = 300.f;
		info.fHp = 50.f;
		info.fSpeed = 150.f;
		info.MCount = 1;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->AddState(new CRunState(STATE_MON::RUN));
		pAI->SetCurState(STATE_MON::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::RANGE:
		break;

	default:
		break;
	}
	assert(pMon);
	return pMon;
}

void CMonster::render()
{
	fPoint pos = GetPos();
 	fPoint scale = GetScale();
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	component_render();
}

void CMonster::update()
{
	if (nullptr != GetAnimator())
	{
		GetAnimator()->update();
	}

	if (nullptr != m_pAI)
	{
		m_pAI->update();
	}
}

float CMonster::GetSpeed()
{
	return Info.fSpeed;
}

const sMonInfo& CMonster::GetMonInfo()
{
	return Info;
}

void CMonster::SetSpeed(float speed)
{
	Info.fSpeed = speed;
}

void CMonster::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CMonster::SetMonInfo(const sMonInfo& info)
{
	Info = info;
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile")
	{
		Info.fHp -= 10.f;
		if (Info.fHp <= 0.f)
			DeleteObj(this);
	}
}

int CMonster::GetMonsterCount()
{
	return Info.MCount;
}

void CMonster::PlusMonsterCount()
{
	Info.MCount++;
}