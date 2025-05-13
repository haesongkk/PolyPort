#include "pch.h"
#include "GameObject.h"

#include "Component.h"
#include "AnimationComponent.h"
#include "BoxComponent.h"
#include "MovementComponent.h"
#include "World.h"
#include "Debug.h"

#include <sstream>


void GameObject::Regame()
{
	m_pRootComponent->SetRelativeTranslation(m_originPos);
	m_bVisible = true;
}

GameObject::GameObject()
	: BaseObject()
{
	m_pRootComponent = AddComponent<TransformComponent>("Transform");
}

GameObject::~GameObject()
{
	for (auto& component : m_pComponents)
	{
  		delete component;
	}
	m_pComponents.clear();
}

bool GameObject::Initialize()
{
	for (auto& component : m_pComponents)
	{
		component->Initialize();
	}
	m_originPos = m_pRootComponent->GetRelativeTranslation();

	return true;
}

void GameObject::Update(float dt)
{
	for (auto& component : m_pComponents)
	{
		component->Update(dt);
	}

}

void GameObject::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto& component : m_pComponents)
	{
		if (!dynamic_cast<RenderComponent*>(component))
			continue;
		dynamic_cast<RenderComponent*>(component)->Render(pRenderTarget);
	}
}

void GameObject::LateUpdate(float dt)
{
}
