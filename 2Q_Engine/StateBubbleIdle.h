#pragma once
#include "FSMState.h"
class StateBubbleIdle :
    public FSMState
{
public:
    StateBubbleIdle(FSM* pOwner)
	    :FSMState(pOwner, "BubbleIdle")
    {}
    virtual ~StateBubbleIdle();

public:
    virtual void Enter() override;
    virtual void Update(float dt) override;
    virtual void Exit() override;

    virtual bool CheckTransition(string& nextState) override;
};

