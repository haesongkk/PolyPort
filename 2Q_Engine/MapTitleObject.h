#pragma once
#include "BitmapComponent.h"
#include "GameObject.h"
class UIComponent;
class MapTitleObject : public GameObject
{
public:
    MapTitleObject();
    virtual ~MapTitleObject();

    virtual void LateUpdate(float dt);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    float m_timer;

    UIComponent* m_pBitmapComponent;
};

