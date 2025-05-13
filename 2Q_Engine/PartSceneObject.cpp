#include "pch.h"
#include "PartSceneObject.h"

#include "BoxCollider.h"
#include "TransformComponent.h"
#include "World.h"
#include "CollisionManager.h"

PartSceneObject::PartSceneObject()
{
	m_pBoxCollider = AddComponent<BoxCollider>("BoxCollider");
	m_pBoxCollider->SetExtends(1000.f, 750.f);

	CollisionManager::GetInstance()->AddScenePart(m_pBoxCollider);
}

PartSceneObject::~PartSceneObject()
{
}

void PartSceneObject::OnCollisionEnter(Collider& other)
{
	m_pWorld->m_prevScene = m_pWorld->m_curScene;
	m_pWorld->m_curScene = this;
	if(m_pWorld->m_prevScene==nullptr)
		m_pWorld->m_prevScene = m_pWorld->m_curScene;
}

void PartSceneObject::OnCollisionExit(Collider& other)
{
	if (m_pWorld->m_curScene == this)
	{
		m_pWorld->m_curScene = m_pWorld->m_prevScene;
	}
}

void PartSceneObject::OnCollisionStay(Collider& other)
{
	
}

