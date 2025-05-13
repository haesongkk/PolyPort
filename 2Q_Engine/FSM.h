#pragma once
#include "AnimationComponent.h"

class FSMComponent;
class FSMState;
class FSMTransition;
class FSM
{
public:
	FSM(FSMComponent* pOwnerComponent, string tag = "")
		: m_pCurrentState(nullptr)
		, m_pInitialState(nullptr)
		, m_pOwnerComponent(pOwnerComponent)
	{

	}
	virtual ~FSM();
protected:
	FSMState* m_pCurrentState;  
	FSMState* m_pInitialState;	
	FSMComponent* m_pOwnerComponent;

	map<string, FSMState*> m_pStates;	// 생성된 FSMState들을 저장하는 컨테이너

	//std::vector<FSMStateAlias*> m_pStateAlias;	// StateAlias 들을 저장하는 컨테이너
public:
	virtual void Update(float DeltaTime);
	void ChangeState(string stateName);
	void SetInitialState(string stateName);
	void AddState(FSMState* pState);
	//void AddStateAlias(FSMStateAlias* pStateAlias);

};

