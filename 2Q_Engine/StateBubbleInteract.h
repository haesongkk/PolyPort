#pragma once
#include "FSMState.h"
class StateBubbleInteract :
    public FSMState
{
public:
    StateBubbleInteract(FSM* pOwner)
        : FSMState(pOwner, "BubbleInteract")
		, m_elapsedTime(0.f)
    {}
    virtual ~StateBubbleInteract() {}

public:
    virtual void Enter() override;
    virtual void Update(float dt) override;
    virtual void Exit() override;

    virtual bool CheckTransition(string& nextState) override;

private:
    float m_elapsedTime;
};

