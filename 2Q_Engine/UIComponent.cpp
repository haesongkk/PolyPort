#include "pch.h"
#include "UIComponent.h"

UIComponent::UIComponent(GameObject* pOwner, const string name, TransformComponent* pRoot)
	:BitmapComponent(pOwner,name,pRoot)
{
	m_opacity = 1.f;
}

void UIComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	if (m_pBitmap == nullptr) return;
	pRenderTarget->SetTransform(m_relativeTransform);
	pRenderTarget->DrawBitmap(m_pBitmap, m_destRect, m_opacity);
}
