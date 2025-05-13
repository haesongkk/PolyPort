#pragma once
#include "FSMState.h"
class StateDash :
    public FSMState
{
public:
    StateDash(FSM* pOwner)
	    :FSMState(pOwner, "Dash")
    {}
    virtual ~StateDash() {}
public:
    virtual void Enter() final;
    virtual void Update(float dt) final;
    virtual void Exit() final;

    virtual bool CheckTransition(string& nextState) override;
};

