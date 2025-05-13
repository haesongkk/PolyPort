#pragma once
#include "FSMState.h"
class StateBubbleBurst :
    public FSMState
{
public:
    StateBubbleBurst(FSM* pOwner)
        : FSMState(pOwner, "BubbleBurst")
    {}
    virtual ~StateBubbleBurst() {}

public:
    virtual void Enter() override;
    virtual void Update(float dt) override;
    virtual void Exit() override;

    virtual bool CheckTransition(string& nextState) override;

};


