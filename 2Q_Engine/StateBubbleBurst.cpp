#include "pch.h"
#include "StateBubbleBurst.h"

#include "FSMCharacter.h"

void StateBubbleBurst::Enter()
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation("Burst", pFSMCharacter->m_bMirror, false);
	pAnimationComponent->SetFrameIndex(0);
}

void StateBubbleBurst::Update(float dt)
{
	FSMState::Update(dt);
}

void StateBubbleBurst::Exit()
{
}

bool StateBubbleBurst::CheckTransition(string& nextState)
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	if(pFSMCharacter->m_bAnimationComplete)
	{
		pFSMCharacter->m_bBurst = false;
		pFSMCharacter->m_bAnimationComplete = false;
		nextState = "BubbleIdle";
		return true;
	}
	return false;
}
