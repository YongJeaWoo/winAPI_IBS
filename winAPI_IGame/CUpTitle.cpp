#include "framework.h"
#include "CUpTitle.h"

CUpTitle* CUpTitle::clone()
{
	return new CUpTitle(*this);
}

CUpTitle::CUpTitle()
{
}

CUpTitle::~CUpTitle()
{
}

void CUpTitle::update()
{
	fPoint pos = GetPos();

	pos.x += m_fSpeed * m_fvDir.x * fDT;
	pos.y += m_fSpeed * m_fvDir.y * fDT;

	SetPos(pos);
	
	// 타이틀 제거
	if (pos.y < -200)
		DeleteObj(this);
}

void CUpTitle::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);
}

void CUpTitle::SetDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}
