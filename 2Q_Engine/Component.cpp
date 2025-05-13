#include "pch.h"
#include "Component.h"

Component::Component(GameObject* pOwner, string name)
	: m_pOwner(pOwner)
	, m_name(name)
{
}

Component::~Component()
{
}

void Component::Update(float dt)
{
}

bool Component::Initialize()
{
	return false;
}

void Component::LateUpdate(float dt)
{
}
