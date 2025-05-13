#include "pch.h"
#include "StateDeath.h"
#include "FSMCharacter.h"
#include "Sound.h"

void StateDeath::Enter()
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
	Sound::Play(SFX, "../Resource/sound/death.mp3");

}

void StateDeath::Update(float dt)
{
	__super::Update(dt);
}

void StateDeath::Exit()
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	MovementComponent* pMovementComponent = pFSMCharacter->m_pMovementComponent;
	RigidBody* pRigidBody = pFSMCharacter->m_pRigidbody;
	pFSMCharacter->m_bDeath = false;
	pMovementComponent->SetMoveSpeed(m_originSpeed);
	pMovementComponent->SetJumpPower(m_originJumpPower);
	pMovementComponent->SetDashSpeed(m_originDashSpeed);
	pRigidBody->SetGravity(m_originGravity);

}

bool StateDeath::CheckTransition(string& nextState)
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	if (pFSMCharacter->m_bDeath && pFSMCharacter->m_bAnimationComplete == true)
	{
		pFSMCharacter->m_bDeath = false;
		pFSMCharacter->m_bAnimationComplete = false;
		pFSMCharacter->m_bRespawn = true;
		nextState = "Idle";
		cout << nextState << endl;
		return true;
	}
	return false;
}
