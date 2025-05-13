#include "pch.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "FSMCharacter.h"
#include "PlayerObject.h"

void RigidBody::Update(float dt)
{
	
	if (!dynamic_cast<PlayerObject*>(m_pOwner)->m_pFSMCharacter->m_bDash)
	{
		if (m_velocity.y > MAX_GRAVITY)
		{
			m_velocity.y = MAX_GRAVITY;
		}

		if (m_velocity.x > 400)
		{
			m_velocity.x = 400;
		}
		if (m_velocity.x < -400)
		{
			m_velocity.x = -400;
		}
	}
	
	m_pParentComponent->AddRelativeTranslation(m_velocity/(1.0/dt));
}

bool RigidBody::IsAffectedGravity()
{
	if (m_gravity != 0)
		return true;
	return false;
}


