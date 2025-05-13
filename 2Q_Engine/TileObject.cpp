#include "pch.h"
#include "TileObject.h"

#include "RigidBody.h"
#include "MovementComponent.h"
#include "TileColliderComponent.h"
#include "Time.h"

#include "Debug.h"

TileObject::TileObject()
	:m_type(),m_bPlayerContact()
{
}

bool TileObject::Initialize()
{
	if (GetComponent<TileColliderComponent>("tileCollider") != nullptr)
		m_type = GetComponent<TileColliderComponent>("tileCollider")->GetCollisionType();
	
	return __super::Initialize();
}

void TileObject::Update(float dt)
{
	__super::Update(dt);
	static float elapsedTime = 0;
	
	if(m_tag == "MOVE")
	{
		if (m_bPlayerContact)
		{
			elapsedTime += dt;
			if(elapsedTime>=3)
				m_pRootComponent->AddRelativeTranslation({ 0,1 });
			//elapsedTime = 0;
		}
	}
	
}

void TileObject::OnCollisionEnter(Collider& other)
{
	if (m_tag == "MOVE")
	{
		if (other.GetOwner()->GetTag() == "player")
			m_bPlayerContact = true;
	}

	
}

void TileObject::OnCollisionExit(Collider& other)
{
	if (other.GetOwner()->GetTag() != "player") return;

}

void TileObject::OnCollisionStay(Collider& other)
{
	if (other.GetOwner()->GetTag() != "player") return;

	
}
