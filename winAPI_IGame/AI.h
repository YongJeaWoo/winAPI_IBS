#pragma once

class CZen;
class CState;

class AI
{
	friend class CZen;

private:
	map<STATE_MON, CState*> m_mapState;
	CZen*	m_pOwner;
	CState* m_pCurState;

public:
	AI();
	~AI();

	CZen* GetOwnerAI();
	CState* GetState(STATE_MON state);
	void SetCurState(STATE_MON state);

	void update();

	void AddState(CState* state);
	void ChangeState(STATE_MON nextState);
};