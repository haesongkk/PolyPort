#include "pch.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "World.h"
#include "CameraObject.h"

RenderComponent::RenderComponent(GameObject* pOwner, const string& Name, TransformComponent* pRoot)
	: TransformComponent(pOwner,Name,pRoot)
	, m_renderingOrder(0)	, m_bVisible(true)
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	m_bVisible = m_pOwner->IsVisible();
	if (m_pOwner->GetOwnerWorld()->m_pCameraObject != nullptr && dynamic_cast<GameObject*>(m_pOwner->GetOwnerWorld()->m_pCameraObject) != m_pOwner)
	{
		pRenderTarget->SetTransform(m_worldTransform * World::m_cameraTransform);
	}
	else
	{
		int a = 0;
	}
}
 