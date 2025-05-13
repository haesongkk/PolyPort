#include "pch.h"
#include "BitmapComponent.h"
#include "Debug.h"
#include "D2DRenderer.h"

BitmapComponent::BitmapComponent(GameObject* pOwner, const string name, TransformComponent* pRoot)
	:RenderComponent(pOwner, name, pRoot), m_pBitmap(), m_destRect()
{
}

BitmapComponent::~BitmapComponent()
{
	// 아예 게임 끝날때 지우거나.. sharingmap에서도 지워야줘야 할 듯
	//if (m_pBitmap != nullptr)	D2DRenderer::m_instance->ReleaseBitmap(m_pBitmap);
}

void BitmapComponent::Update(float dt)
{
	RenderComponent::Update(dt);
}

void BitmapComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	if(m_bVisible)
	{
		if (m_pBitmap == nullptr) return;
		pRenderTarget->DrawBitmap(m_pBitmap, m_destRect, m_opacity);
	}
}

Vector2D BitmapComponent::SetBitmap(const wstring bitmapKey)
{
	m_bitmapKey = bitmapKey;

	if (bitmapKey == L"") 
		m_pBitmap = nullptr;
	else m_pBitmap = D2DRenderer::m_instance->CreateBitmapFromFile(bitmapKey);

	if (m_pBitmap == nullptr) return { 0,0 };
	D2D1_SIZE_F size = m_pBitmap->GetSize();
	m_destRect.top = -size.height /2;
	m_destRect.left = -size.width /2;
	m_destRect.right = size.width/2;
	m_destRect.bottom = size.height/2;
	return { size.width,size.height };
}

wstring BitmapComponent::GetBitmapkey()
{
	return m_bitmapKey;
}
