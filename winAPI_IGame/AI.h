#pragma once

class CMonster;
class CState;

class AI
{
	friend class CMonster;

private:
	map<MON_STATE, CState*> m_mapState;
	CMonster* m_pOwner;
	CState* m_pCurState;

public:
	void AddState(CState* pState);

public:
	AI();
	~AI();


};