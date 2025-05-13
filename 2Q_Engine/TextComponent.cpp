#include "pch.h"
#include "TextComponent.h"

#include "D2DRenderer.h"
#include "Debug.h"

TextComponent::TextComponent(GameObject* pOwner, const string name, TransformComponent* pRoot)
	:RenderComponent(pOwner,name,pRoot)
{
}

TextComponent::~TextComponent()
{
	if (m_pBursh != nullptr) m_pBursh->Release();
	if (m_pWriteTextFormat != nullptr) m_pWriteTextFormat->Release();
}

void TextComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	Debug::Rect(m_relativeTransform, { m_rect.right - m_rect.left,m_rect.bottom - m_rect.top }, false);
	m_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	pRenderTarget->SetTransform(m_relativeTransform);
	pRenderTarget->DrawText(m_text.c_str(), wcslen(m_text.c_str()), m_pWriteTextFormat, m_rect, m_pBursh);
}

void TextComponent::SetTextFormat(const wstring& font, int size)
{
	if (m_pWriteTextFormat != nullptr) m_pWriteTextFormat->Release();
	D2DRenderer::m_pDWriteFactory->CreateTextFormat(font.c_str(), NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &m_pWriteTextFormat);
}

void TextComponent::SetColor(float r, float g, float b, float alpha)
{
	if (m_pBursh != nullptr) m_pBursh->Release();
	D2DRenderer::m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(r / 255, g / 255, b / 255, alpha), &m_pBursh);
}

void TextComponent::SetTextBox(float x, float y, float dx, float dy)
{
	m_relativeTranslation = { x,y };
	m_rect = { -dx / 2,-dy / 2 ,+dx / 2 , +dy / 2 };
}

void TextComponent::SetText(const wstring& text)
{
	m_text = text;
}
