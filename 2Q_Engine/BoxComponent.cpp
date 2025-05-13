#include "pch.h"
#include "BoxComponent.h"

#include "D2DRenderer.h"
#include "GameObject.h"
#include "World.h"

#include "CameraObject.h"
void BoxComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	ID2D1SolidColorBrush* pBrush = D2DRenderer::m_instance->GetBrush();
	
	pBrush->SetColor(m_color);
	

	
	D2D1_RECT_F rect = { -width, -height, width, height };
	__super::Render(pRenderTarget);
	if(m_bVisible)
	{
		pRenderTarget->DrawRectangle(rect, pBrush);
	}
}

void BoxComponent::Update(float dt)
{
	__super::Update(dt);
	D2D1_MATRIX_3X2_F transform;
	if (m_pParentComponent != nullptr)
	{
		m_worldTransform = m_relativeTransform * m_pParentComponent->GetWorldTransform();
		if (!dynamic_cast<CameraObject*>(m_pOwner))
		{
			m_worldTransform = m_worldTransform;
		}
	}
	else
	{
		m_worldTransform = m_relativeTransform;
	}
}

bool BoxComponent::Initialize()
{
	return false;
}

