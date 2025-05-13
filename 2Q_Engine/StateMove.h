#pragma once
#include "FSMState.h"
class StateMove :
    public FSMState
{
public:
    StateMove(FSM* pOwner)
        : FSMState(pOwner, "Move")
    {}
    virtual ~StateMove() {}

public:
    virtual void Enter() override;
    virtual void Update(float dt) override;
    virtual void Exit() override;

    virtual bool CheckTransition(string& nextState) override;
};

