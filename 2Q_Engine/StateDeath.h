#pragma once
#include "FSMState.h"
#include "MovementComponent.h"
#include "RigidBody.h"

class StateDeath :
    public FSMState
{
public:
    StateDeath(FSM* pOwner)
        : FSMState(pOwner, "Death")
        , m_originSpeed(0.f)
    {}
    virtual ~StateDeath() {}

public:
    virtual void Enter() override;
    virtual void Update(float dt) override;
    virtual void Exit() override;

    virtual bool CheckTransition(string& nextState) override;

private:
    float m_originSpeed;
    float m_originGravity;
    float m_originJumpPower;
    float m_originDashSpeed;
};

