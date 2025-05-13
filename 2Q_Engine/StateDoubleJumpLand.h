#pragma once
#include "FSMState.h"
#include "MovementComponent.h"

class StateDoubleJumpLand
	:public FSMState
{
public:
    StateDoubleJumpLand(FSM* pOwner)
	    :FSMState(pOwner,"DoubleJumpLand")
    {}
    virtual ~StateDoubleJumpLand() {}
public:
    virtual void Enter() final;
    virtual void Update(float dt) final;
    virtual void Exit() final;

    virtual bool CheckTransition(string& nextState) override;
    float m_originSpeed;
};

