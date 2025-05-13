#include "pch.h"
#include "StateBubbleIdle.h"

#include "FSMCharacter.h"

StateBubbleIdle::~StateBubbleIdle()
{
}

void StateBubbleIdle::Enter()
{
	FSMCharacter* pFsmCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFsmCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation("Idle", false, true);
	pAnimationComponent->SetFrameIndex(0);
}

void StateBubbleIdle::Update(float dt)
{
	__super::Update(dt);
}

void StateBubbleIdle::Exit()
{
}

bool StateBubbleIdle::CheckTransition(string& nextState)
{
	FSMCharacter* pFSMCharacter = dynamic_cast<FSMCharacter*>(m_pOwner);
	if(pFSMCharacter->m_bInteract)
	{
		nextState = "BubbleInteract";
		return true;
	}
	return false;
}
