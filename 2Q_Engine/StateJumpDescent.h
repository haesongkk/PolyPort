#pragma once
#include "FSMState.h"
class StateJumpDescent :
    public FSMState
{
public:
    StateJumpDescent(FSM* pOwner)
	    :FSMState(pOwner, "JumpDescent")
    {}
    virtual ~StateJumpDescent() {}
public:
    virtual void Enter() final;
    virtual void Update(float dt) final;
    virtual void Exit() final;

    virtual bool CheckTransition(string& nextState) override;
};

