#include "pch.h"
#include "StateTeleport.h"
#include "FSMCharacter.h"

void StateTeleport::Enter()
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation("Death", pFSMCharacter->m_bMirror, false);
	pAnimationComponent->SetFrameIndex(0);
	MovementComponent* pMovementComponent = pFSMCharacter->m_pMovementComponent;
	RigidBody* pRigidBody = pFSMCharacter->m_pRigidbody;
	m_originSpeed = pMovementComponent->GetMoveSpeed();
	m_originJumpPower = pMovementComponent->GetJumpPower();
	m_originDashSpeed = pMovementComponent->GetDashSpeed();
	m_originGravity = pRigidBody->GetGravity();
	pMovementComponent->SetMoveSpeed(0.f);
	pMovementComponent->SetJumpPower(0.f);
	pMovementComponent->SetDashSpeed(0.f);
	pRigidBody->SetGravity(0.f);
	pRigidBody->SetVelocity({ 0.f,0.f });


	if (pFSMCharacter->m_moveDirection.x > 0)
	{
		pFSMCharacter->m_bMirror = false;

	}
	else if (pFSMCharacter->m_moveDirection.x < 0)
	{
		pFSMCharacter->m_bMirror = true;

	}
	pAnimationComponent->SetAnimation("Teleport", pFSMCharacter->m_bMirror, false);
	pAnimationComponent->SetFrameIndex(0);
}

void StateTeleport::Update(float dt)
{
	__super::Update(dt);
}

void StateTeleport::Exit()
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	MovementComponent* pMovementComponent = pFSMCharacter->m_pMovementComponent;
	RigidBody* pRigidBody = pFSMCharacter->m_pRigidbody;
	pFSMCharacter->m_bTeleport = false;
	pFSMCharacter->m_bDeath = false;
	pMovementComponent->SetMoveSpeed(m_originSpeed);
	pMovementComponent->SetJumpPower(m_originJumpPower);
	pMovementComponent->SetDashSpeed(m_originDashSpeed);
	pRigidBody->SetGravity(m_originGravity);
}

bool StateTeleport::CheckTransition(string& nextState)
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	if (pFSMCharacter->m_bBubble)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "Bubble";
		cout << nextState << endl;
		return true;
	}
	if(pFSMCharacter->m_bAnimationComplete)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "Idle";
		cout << nextState << endl;
		return true;
	}
	return false;
}
