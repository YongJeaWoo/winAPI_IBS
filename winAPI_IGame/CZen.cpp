#include "framework.h"
#include "CZen.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CD2DImage.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CRunState.h"

CZen::CZen()
{
	CD2DImage* pRImg = CResourceManager::getInst()->LoadD2DImage(L"Zen", L"texture\\enemy\\Zen_Move_Right.png");
	SetName(L"Zen");
	SetScale(fVec2(80.f, 80.f));

	CreateCollider();
	GetCollider()->SetScale(fVec2(70.f, 70.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Move_Right", pRImg, fVec2(0.f, 0.f), fVec2(31.25f, 22.f), fVec2(31.25f, 0.f), 1.f, 4, false);
	GetAnimator()->Play(L"Move_Right");

	Info = {};
	m_pAI = nullptr;
}

CZen::~CZen()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

CZen* CZen::Clone()
{
	CZen* newMonster = new CZen;
	if (nullptr != m_pAI)
		newMonster->m_pAI = new AI;

	return new CZen(*newMonster);
}

CZen* CZen::Create(MON_TYPE type, fPoint pos)
{
	CZen* pMon = nullptr;

	switch (type)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CZen;
		pMon->SetPos(pos);

		MonInfo info = {};
		// info.fAtt = 10.f;
		info.fRecogRange = 300.f;
		info.fHp = 50.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->AddState(new CRunState(STATE_MON::RUN));
		pAI->SetCurState(STATE_MON::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::SHOOT:
		break;

	default:
		break;
	}
	assert(pMon);
	return pMon;
}

void CZen::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	component_render();
}

void CZen::update()
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

float CZen::GetSpeed()
{
	return Info.fSpeed;
}

const MonInfo& CZen::GetMonInfo()
{
	return Info;
}

void CZen::SetSpeed(float speed)
{
	Info.fSpeed = speed;
}

void CZen::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CZen::SetMonInfo(const MonInfo& info)
{
	Info = info;
}

void CZen::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile")
	{
		Info.fHp -= 10.f;
		if (Info.fHp <= 0.f)
			DeleteObj(this);
	}
}
