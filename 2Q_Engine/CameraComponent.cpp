#include "pch.h"
#include "CameraComponent.h"



#include "CameraObject.h"
#include "World.h"
#include "GameObject.h"
#include "PartSceneObject.h"

CameraComponent::CameraComponent(GameObject* pOwner, string name, TransformComponent* pRoot)
	: TransformComponent(pOwner, name, pRoot)
	, m_inversedTransform{}
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update(float dt)
{
	if (m_pOwner->GetOwnerWorld()->m_curScene != nullptr)
	{
		BoxCollider* curPartScene = m_pOwner->GetOwnerWorld()->m_curScene->m_pBoxCollider;
		Vector2D extends = dynamic_cast<CameraObject*>(m_pOwner)->GetBoxCollider()->GetExtends();

		m_pOwner->GetRootComponent()->SetWorldTransform(dynamic_cast<CameraObject*>(m_pOwner)->GetFocusingObject()->GetRootComponent()->GetWorldTransform());

		if (m_pOwner->GetRootComponent()->GetWorldTransform()._31 < curPartScene->GetMinColliderVector().x + extends.x)
		{
			m_pOwner->GetRootComponent()->GetWorldTransform()._31 += 4000.f * dt * ++m_left;
			if(m_pOwner->GetRootComponent()->GetWorldTransform()._31 > curPartScene->GetMinColliderVector().x + extends.x)
			{
				m_pOwner->GetRootComponent()->GetWorldTransform()._31 = curPartScene->GetMinColliderVector().x + extends.x;
			}
			//m_pOwner->GetRootComponent()->GetWorldTransform()._31 = curPartScene->GetMinColliderVector().x + extends.x;
		}
		else
			m_left = 0;
		if (m_pOwner->GetRootComponent()->GetWorldTransform()._31 > curPartScene->GetMaxColliderVector().x - extends.x)
		{
			m_pOwner->GetRootComponent()->GetWorldTransform()._31 -= 4000.f * dt * ++m_right;
			if(m_pOwner->GetRootComponent()->GetWorldTransform()._31 < curPartScene->GetMaxColliderVector().x - extends.x)
			{
				m_pOwner->GetRootComponent()->GetWorldTransform()._31 = curPartScene->GetMaxColliderVector().x - extends.x;
			}
			//m_pOwner->GetRootComponent()->GetWorldTransform()._31 = curPartScene->GetMaxColliderVector().x - extends.x;
		}
		else
			m_right = 0;
		if (m_pOwner->GetRootComponent()->GetWorldTransform()._32 < curPartScene->GetMinColliderVector().y + extends.y)
		{
			m_pOwner->GetRootComponent()->GetWorldTransform()._32 += 4000.f * dt * ++m_top;
			if(m_pOwner->GetRootComponent()->GetWorldTransform()._32 > curPartScene->GetMinColliderVector().y + extends.y)
			{
				m_pOwner->GetRootComponent()->GetWorldTransform()._32 = curPartScene->GetMinColliderVector().y + extends.y;
			}
			//m_pOwner->GetRootComponent()->GetWorldTransform()._32 = curPartScene->GetMinColliderVector().y + extends.y;
		}
		else
			m_top = 0;
		if (m_pOwner->GetRootComponent()->GetWorldTransform()._32 > curPartScene->GetMaxColliderVector().y - extends.y)
		{
			m_pOwner->GetRootComponent()->GetWorldTransform()._32 -= 4000.f * dt * ++m_bottom;
			if(m_pOwner->GetRootComponent()->GetWorldTransform()._32 < curPartScene->GetMaxColliderVector().y - extends.y)
			{
				m_pOwner->GetRootComponent()->GetWorldTransform()._32 = curPartScene->GetMaxColliderVector().y - extends.y;
			}
			//m_pOwner->GetRootComponent()->GetWorldTransform()._32 = curPartScene->GetMaxColliderVector().y - extends.y;
		}
		else
			m_bottom = 0;
	}
	__super::Update(dt);
}

bool CameraComponent::Initialize()
{
	return false;
}