#include "pch.h"
#include "DemoObject.h"

#include "BoxComponent.h"
#include "BoxCollider.h"
#include "World.h"
#include "CollisionManager.h"

DemoObject::DemoObject()
    :GameObject()
{
    AddComponent<BoxComponent>("BoxComponent");

    m_pBoxCollider = AddComponent<BoxCollider>("BoxCollider");
    CollisionManager::GetInstance()->AddCollider(m_pBoxCollider);
    m_pBoxCollider->SetExtends(500.f, 500.f);
    m_pRootComponent->SetRelativeTranslation({ 100.f,100.f });
}





void DemoObject::Update(float dt)
{
   __super::Update(dt);
}

bool DemoObject::Initialize()
{
    //m_pRootComponent->SetParentTransformComponent(m_pWorld->GetCameraTransform());
    return true;
}
