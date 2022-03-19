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
	AI();
	~AI();

	void update();

	CState* GetState(MON_STATE state);
	void SetCurState(MON_STATE state);

	void AddState(CState* state);
};