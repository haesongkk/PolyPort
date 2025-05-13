#pragma once
#include "BitmapComponent.h"
class UIComponent :public BitmapComponent
{
public:
	UIComponent(GameObject* pOwner, const string name, TransformComponent* pRoot);
	virtual ~UIComponent() { }

public:
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	virtual void Update(float dt) override { __super::Update(dt); }
};

