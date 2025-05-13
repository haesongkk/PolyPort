#include "pch.h"
#include "StateJump.h"
#include "FSMCharacter.h"

void StateJump::Enter()
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);	
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;

	if (pFSMCharacter->m_pRigidbody->GetVelocity().x > 0)
	{
		pFSMCharacter->m_bMirror = false;

	}
	else if (pFSMCharacter->m_pRigidbody->GetVelocity().x < 0)
	{
		pFSMCharacter->m_bMirror = true;

	}
	pAnimationComponent->SetAnimation("Jump", pFSMCharacter->m_bMirror, false);
	pAnimationComponent->SetFrameIndex(0);
}

void StateJump::Update(float dt)
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);

	if (pFSMCharacter->m_prevDirection.x != pFSMCharacter->m_moveDirection.x)
	{
		AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
		if (pFSMCharacter->m_moveDirection.x > 0)
		{
			pFSMCharacter->m_bMirror = false;

		}
		else if (pFSMCharacter->m_moveDirection.x < 0)
		{
			pFSMCharacter->m_bMirror = true;
		}
		pAnimationComponent->SetReverse(pFSMCharacter->m_bMirror);
	}

	__super::Update(dt);
}

void StateJump::Exit()
{
}

bool StateJump::CheckTransition(string& nextState)
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	if (pFSMCharacter->m_bLand)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "JumpLand";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_bDeath)
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
	if (pFSMCharacter->m_bAnimationComplete && pFSMCharacter->m_moveDirection.y > 0.0f)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "JumpDescent";
		cout << nextState << endl;
		return true;
	}
	if(pFSMCharacter->m_jumpCount == 0)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "DoubleJump";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_bDash)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "Dash";
		cout << nextState << endl;
		return true;
	}
	// 2������
	return false;
}
