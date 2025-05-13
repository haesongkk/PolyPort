#pragma once
#include "FSMState.h"

class StateDoubleJump
	:public FSMState
{
public:
    StateDoubleJump(FSM* pOwner)
        :FSMState(pOwner, "DoubleJump")
    {}
    virtual ~StateDoubleJump() {}
public:
    virtual void Enter() final;
    virtual void Update(float dt) final;
    virtual void Exit() final;

    virtual bool CheckTransition(string& nextState) override;
};

