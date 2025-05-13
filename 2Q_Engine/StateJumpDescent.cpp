#include "pch.h"
#include "StateJumpDescent.h"
#include "FSMCharacter.h"

void StateJumpDescent::Enter()
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
	pAnimationComponent->SetAnimation("JumpDescent", pFSMCharacter->m_bMirror, false);
	pAnimationComponent->SetFrameIndex(0);
}

void StateJumpDescent::Update(float dt)
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
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

void StateJumpDescent::Exit()
{
}

bool StateJumpDescent::CheckTransition(string& nextState)
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
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
	if (pFSMCharacter->m_bDash)
	{
		nextState = "Dash";
		cout << nextState << endl;
		pFSMCharacter->m_bAnimationComplete = false;
		return true;
	}
	if (pFSMCharacter->m_bAnimationComplete && pFSMCharacter->m_bLand)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "JumpLand";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_jumpCount == 0)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "DoubleJump";
		cout << nextState << endl;
		return true;
	}
	//2´Ü Á¡ÇÁ
	return false;
}
