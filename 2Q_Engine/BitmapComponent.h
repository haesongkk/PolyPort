#pragma once
#include "RenderComponent.h"
class BitmapComponent : public RenderComponent
{
public:
	BitmapComponent(GameObject* pOwner, const string name, TransformComponent* pRoot);
	virtual ~BitmapComponent();

public:
	virtual void Update(float dt) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;

	Vector2D SetBitmap(const wstring bitmapKey);
	wstring GetBitmapkey();

protected:
	ID2D1Bitmap* m_pBitmap;

	D2D1_RECT_F m_destRect;
	wstring m_bitmapKey;
	FLOAT m_opacity = 1.f;

public:
	void SetOpacity(const float opc) { m_opacity = opc; }
	float GetOpacity() const { return m_opacity; }
};

