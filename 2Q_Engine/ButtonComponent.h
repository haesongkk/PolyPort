#pragma once
#include "UIComponent.h"
class ButtonComponent : public UIComponent
{
public:
	ButtonComponent(GameObject* pOwner, const string name, TransformComponent* pRoot);
	virtual ~ButtonComponent() { }

public:
	virtual void Update(float dt) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

	void SetActiveBitmap(wstring _active);
	void SetDefaultBitmap(wstring _default);
	void SetButtonRect(float x, float y, float dx, float dy);

private:
	D2D1_RECT_F m_buttonRect;
	ID2D1Bitmap* m_pActiveBitmap;
	ID2D1Bitmap* m_pDefaultBitmap;
	bool m_bOnButton;
	bool m_preOnButton;
};

