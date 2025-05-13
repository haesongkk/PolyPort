#pragma once
#include "FSMState.h"
#include "MovementComponent.h"

class StateTeleport
	:public FSMState
{
public:
    StateTeleport(FSM* pOwner)
	    : FSMState(pOwner, "Teleport")
	{}
    virtual ~StateTeleport(){}
public:
    virtual void Enter() final;
    virtual void Update(float dt) final;
    virtual void Exit() final;

    virtual bool CheckTransition(string& nextState) override;
    float m_originSpeed;
    float m_originJumpPower;
    float m_originDashSpeed;
    float m_originGravity;
};

