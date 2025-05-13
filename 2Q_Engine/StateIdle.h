#pragma once
#include "FSMState.h"
class StateIdle :
    public FSMState
{
public:
    StateIdle(FSM* pOwner)
        : FSMState(pOwner, "Idle")
    {}
    virtual ~StateIdle() {}

public:
    virtual void Enter() override;
    virtual void Update(float dt) override;
    virtual void Exit() override;

    virtual bool CheckTransition(string& nextState) override;
};

