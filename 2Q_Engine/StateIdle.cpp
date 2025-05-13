#include "pch.h"
#include "StateIdle.h"
#include "FSMCharacter.h"

void StateIdle::Enter()
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation("Idle", pFSMCharacter->m_bMirror, true);
	pAnimationComponent->SetFrameIndex(0);
	if (pFSMCharacter->m_bLand)
	{
		pFSMCharacter->m_jumpCount = 2;
		pFSMCharacter->m_DashCount = 1;
	}
}

void StateIdle::Update(float dt)
{
	__super::Update(dt);
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	
}

void StateIdle::Exit()
{
}

bool StateIdle::CheckTransition(string& nextState)
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	if(pFSMCharacter->m_bDeath)
	{
		nextState = "Death";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_bBubble)
	{
		nextState = "Bubble";
		cout << nextState << endl;
		return true;
	}
	if(!pFSMCharacter->m_bLand && pFSMCharacter->m_pRigidbody->GetVelocity().y < 0.f && pFSMCharacter->m_jumpCount == 2)
	{
		nextState = "Jump";
		cout << nextState << endl;
		return true;
	}
	if (!pFSMCharacter->m_bLand && pFSMCharacter->m_pRigidbody->GetVelocity().y < 0.f && pFSMCharacter->m_jumpCount == 1)
	{
		nextState = "DoubleJump";
		cout << nextState << endl;
		return true;
	}
	if (!pFSMCharacter->m_bLand && pFSMCharacter->m_pRigidbody->GetVelocity().y > 0.f)
	{
		nextState = "JumpDescent";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_moveDirection.x != 0.0f || pFSMCharacter->m_moveDirection.y != 0.0f)
	{
		nextState = "Move";
		cout << nextState << endl;
		return true;
	}
	if(pFSMCharacter->m_bDash)
	{
		nextState = "Dash";
		cout << nextState << endl;
		return true;
	}
	return false;
}
