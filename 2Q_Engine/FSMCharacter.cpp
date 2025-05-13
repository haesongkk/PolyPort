#include "pch.h"
#include "FSMCharacter.h"


void FSMCharacter::Update(float DeltaTime)
{
	if(m_pRigidbody != nullptr)
	{
		m_prevDirection = m_moveDirection;
		m_moveDirection = m_pRigidbody->GetVelocity();
	}
	

	FSM::Update(DeltaTime);
}
