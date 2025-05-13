#include "pch.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "World.h"
#include "CameraObject.h"

TransformComponent::TransformComponent(GameObject* pOwner, string Name, TransformComponent* pRoot)
	: Component(pOwner, Name)
	, m_relativeRotation(0.f)
	, m_relativeScale({ 1.f,1.f })
	, m_relativeTranslation({ 0.f,0.f })
	, m_relativeTransform(D2D1::Matrix3x2F::Identity())
	, m_worldTransform(D2D1::Matrix3x2F::Identity())
	, m_pParentComponent(pRoot)
{
	/*m_relativeTransform = D2D1::Matrix3x2F::Scale(m_relativeScale.x, m_relativeScale.y)
		* D2D1::Matrix3x2F::Rotation(m_relativeRotation)
		* D2D1::Matrix3x2F::Translation(m_relativeTranslation.x, m_relativeTranslation.y);

	if (m_pParentComponent != nullptr)
	{
		m_worldTransform = m_relativeTransform * m_pParentComponent->GetWorldTransform();
	}
	else
	{
		m_worldTransform = m_relativeTransform;
	}*/

}
TransformComponent::~TransformComponent()
{
}

bool TransformComponent::Initialize()
{
	return false;
}

void TransformComponent::Update(float dt)
{
	m_relativeTransform = D2D1::Matrix3x2F::Scale(m_relativeScale.x, m_relativeScale.y)
		* D2D1::Matrix3x2F::Rotation(m_relativeRotation, {0,0})
		* D2D1::Matrix3x2F::Translation(m_relativeTranslation.x, m_relativeTranslation.y);

	if (m_pParentComponent != nullptr)
	{
		m_worldTransform = m_relativeTransform * m_pParentComponent->GetWorldTransform();
	}
	else
	{
		m_worldTransform = m_relativeTransform;
	}

	

	/*if (m_pOwner->GetParentObject() != nullptr)
	{
		m_worldTransform = m_worldTransform * m_pOwner->GetParentObject()->GetRootComponent()->GetWorldTransform();
	}*/
}
