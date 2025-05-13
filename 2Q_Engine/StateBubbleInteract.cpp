#include "pch.h"
#include "StateBubbleInteract.h"
#include "FSMCharacter.h"

void StateBubbleInteract::Enter()
{
	FSMCharacter* pFsmCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFsmCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation("Idle", false, true);
	pAnimationComponent->SetFrameIndex(0);
}

void StateBubbleInteract::Update(float dt)
{
	FSMState::Update(dt);
	//m_elapsedTime += dt;
}

void StateBubbleInteract::Exit()
{
	//m_elapsedTime = 0.f;
}

bool StateBubbleInteract::CheckTransition(string& nextState)
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	if(pFSMCharacter->m_bDeath)
	{
		pFSMCharacter->m_bInteract = false;
		nextState = "Death";
		return true;
	}
	if (pFSMCharacter->m_bBurst)
	{
		pFSMCharacter->m_bInteract = false;
		nextState = "BubbleBurst";
		return true;
	}
	return false;
}
