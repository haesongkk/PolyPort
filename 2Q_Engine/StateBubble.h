#pragma once
#include "FSMState.h"
#include "MovementComponent.h"
#include "RigidBody.h"

class StateBubble :
    public FSMState
{
public:
    StateBubble(FSM* pOwner)
	    : FSMState(pOwner, "Bubble")
    {}
    virtual ~StateBubble() {}
public:
    virtual void Enter() final;
    virtual void Update(float dt) final;
    virtual void Exit() final;

    virtual bool CheckTransition(string& nextState) override;
    float m_originSpeed;
    float m_originDashSpeed;
    float m_originGravity;
    float m_originJumpPower;
};

