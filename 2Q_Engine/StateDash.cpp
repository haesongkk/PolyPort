#include "pch.h"
#include "StateDash.h"

#include "FSMCharacter.h"

void StateDash::Enter()
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
	pAnimationComponent->SetAnimation("Dash", pFSMCharacter->m_bMirror, false);
	pAnimationComponent->SetFrameIndex(0);
}

void StateDash::Update(float dt)
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

void StateDash::Exit()
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	pFSMCharacter->m_bDash = false;
}

bool StateDash::CheckTransition(string& nextState)
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	if(pFSMCharacter->m_bDeath)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "Death";
		cout << nextState << endl;
		return true;
	}
	if(pFSMCharacter->m_bBubble)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "Bubble";
		cout << nextState << endl;
		return true;
	}
	if (pFSMCharacter->m_bAnimationComplete == true||!pFSMCharacter->m_bDash)
	{
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "Idle";
		cout << nextState << endl;
		return true;
	}

	return false;
}
