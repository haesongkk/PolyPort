#include "pch.h"
#include "StateMove.h"
#include "FSMCharacter.h"

void StateMove::Enter()
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
	pAnimationComponent->SetAnimation("Move", pFSMCharacter->m_bMirror, true);
	pAnimationComponent->SetFrameIndex(0);
}

void StateMove::Update(float dt)
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

void StateMove::Exit()
{
}

bool StateMove::CheckTransition(string& nextState)
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	if (pFSMCharacter->m_bDeath)
	{
		nextState = "Death";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_moveDirection.x == 0.0f && pFSMCharacter->m_moveDirection.y == 0.0f)
	{
		nextState = "Idle";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_bDash)
	{
		nextState = "Dash";
		cout << nextState << endl;
		return true;
	}
	if(pFSMCharacter->m_bBubble)
	{
		nextState = "Bubble";
		cout << nextState << endl;
		return true;
	}
	if (!pFSMCharacter->m_bLand && pFSMCharacter->m_moveDirection.y < 0.f)
	{
		nextState = "Jump";
		cout << nextState << endl;
		return true;
	}
	if(pFSMCharacter->m_moveDirection.y > 0)
	{
		nextState = "JumpDescent";
		cout << nextState << endl;
		return true;
	}
    return false;
}
