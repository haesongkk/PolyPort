#pragma once
#include "FSMState.h"
#include "MovementComponent.h"

class StateJumpLand
	: public FSMState
{
public:
    StateJumpLand(FSM* pOwner)
	    :FSMState(pOwner, "JumpLand")
    {}
    virtual ~StateJumpLand(){}
public:
    virtual void Enter() final;
    virtual void Update(float dt) final;
    virtual void Exit() final;

    virtual bool CheckTransition(string& nextState) override;
    float m_originSpeed;
};

