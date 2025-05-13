#include "pch.h"
#include "MapTitleObject.h"

#include "BitmapComponent.h"
#include "Input.h"
#include "UIComponent.h"
#include "Event.h"

MapTitleObject::MapTitleObject()
{
	m_pBitmapComponent = AddComponent<UIComponent>("BitmapComponent");
	m_pBitmapComponent->SetRelativeTranslation({ 960,600 });
}

MapTitleObject::~MapTitleObject()
{
}

void MapTitleObject::LateUpdate(float dt)
{
	m_timer += dt;
	m_pBitmapComponent->SetOpacity(1 - m_timer / 5);
	if (1 - m_timer / 5 < 0) Event::DeleteObject(this);
}

void MapTitleObject::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
