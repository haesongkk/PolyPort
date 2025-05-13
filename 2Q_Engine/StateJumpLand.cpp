#include "pch.h"
#include "StateJumpLand.h"
#include "FSMCharacter.h"

void StateJumpLand::Enter()
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;

	if (pFSMCharacter->m_moveDirection.x > 0)
	{
		pFSMCharacter->m_bMirror = false;

	}
	else if (pFSMCharacter->m_moveDirection.x < 0)
	{
		pFSMCharacter->m_bMirror = true;

	}
	pAnimationComponent->SetAnimation("JumpLand", pFSMCharacter->m_bMirror, false);
	pAnimationComponent->SetFrameIndex(0);

	MovementComponent* pMovementComponent = pFSMCharacter->m_pMovementComponent;
	m_originSpeed = pMovementComponent->GetMoveSpeed();
	pMovementComponent->SetMoveSpeed(0);

	pFSMCharacter->m_jumpCount = 2;
	pFSMCharacter->m_DashCount = 1;
}

void StateJumpLand::Update(float dt)
{
	__super::Update(dt);
}

void StateJumpLand::Exit()
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	MovementComponent* pMovementComponent = pFSMCharacter->m_pMovementComponent;
	pMovementComponent->SetMoveSpeed(m_originSpeed);
}

bool StateJumpLand::CheckTransition(string& nextState)
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	if(pFSMCharacter->m_bDeath)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "Death";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_bBubble)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "Bubble";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_bAnimationComplete == true)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "Idle";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_bLand == false && pFSMCharacter->m_moveDirection.y < 0)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "Jump";
		cout << nextState << endl;
		return true;
	}
	return false;
}
