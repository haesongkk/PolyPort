#include "pch.h"
#include "StateBubble.h"
#include "FSMCharacter.h"
void StateBubble::Enter()
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation("Bubble", pFSMCharacter->m_bMirror, true);
	pAnimationComponent->SetFrameIndex(0);

	MovementComponent* pMovementComponent = pFSMCharacter->m_pMovementComponent;
	m_originSpeed = pMovementComponent->GetMoveSpeed();
	m_originDashSpeed = pMovementComponent->GetDashSpeed();
	m_originJumpPower = pMovementComponent->GetJumpPower();
	pMovementComponent->SetMoveSpeed(0.f);
	pMovementComponent->SetDashSpeed(0.f);
	pMovementComponent->SetJumpPower(0.f);

	RigidBody* pRigidBody = pFSMCharacter->m_pRigidbody;
	m_originGravity = pRigidBody->GetGravity();
	pRigidBody->SetGravity(0);
	pRigidBody->SetVelocity({ 0.f,0.f });

	pFSMCharacter->m_jumpCount = 2;
	pFSMCharacter->m_DashCount = 1;
}

void StateBubble::Update(float dt)
{
	__super::Update(dt);
}

void StateBubble::Exit()
{ 
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	MovementComponent* pMovementComponent = pFSMCharacter->m_pMovementComponent;
	RigidBody* pRigidBody = pFSMCharacter->m_pRigidbody;
	pFSMCharacter->m_bLand = false;
	pMovementComponent->SetMoveSpeed(m_originSpeed);
	pMovementComponent->SetDashSpeed(m_originDashSpeed);
	pMovementComponent->SetJumpPower(m_originJumpPower);
	pRigidBody->SetGravity(m_originGravity);
	//pFSMCharacter->m_bBubble = false;
}

bool StateBubble::CheckTransition(string& nextState)
{
	//클릭하면
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	if(pFSMCharacter->m_bDeath)
	{
		nextState = "Death";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_bTeleport)
	{
		nextState = "Teleport";
		cout << nextState << endl;
		return true;
	}
	if(pFSMCharacter->m_bBubble==false)
	{
		nextState = "Idle";
		cout << nextState << endl;
		return true;
	}
	return false;
}
