#pragma once
#include "RenderComponent.h"
class TextComponent : public RenderComponent
{
public:
	TextComponent(GameObject* pOwner, const string name, TransformComponent* pRoot);
	virtual ~TextComponent();

public:
	virtual void Update(float dt) override { 
		__super::Update(dt); }
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	
	void SetTextFormat(const wstring& font, int size);
	void SetColor(float r, float g, float b, float alpha = 1);
	void SetTextBox(float x, float y, float dx, float dy);
	void SetText(const wstring& text);

protected:
	ID2D1SolidColorBrush* m_pBursh;
	IDWriteTextFormat* m_pWriteTextFormat;
	D2D1_RECT_F m_rect;
	wstring m_text;

};

