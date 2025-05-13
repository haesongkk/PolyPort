#pragma once
#include "FSMState.h"

class StateDoubleJumpDescent
	:public FSMState
{
public:
    StateDoubleJumpDescent(FSM* pOwner)
	    :FSMState(pOwner, "DoubleJumpDescent")
    {}
    virtual ~StateDoubleJumpDescent() {}
public:
    virtual void Enter() final;
    virtual void Update(float dt) final;
    virtual void Exit() final;

    virtual bool CheckTransition(string& nextState) override;
};

