#pragma once
#include "FSMState.h"
class StateJump :
    public FSMState
{
public:
    StateJump(FSM* pOwner)
        :FSMState(pOwner, "Jump")
    {}
    virtual ~StateJump() {}
public:
    virtual void Enter() final;
    virtual void Update(float dt) final;
    virtual void Exit() final;

    virtual bool CheckTransition(string& nextState) override;
};

