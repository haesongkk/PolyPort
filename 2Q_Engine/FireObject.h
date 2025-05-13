#pragma once
#include "GameObject.h"
class BoxCollider;
class AnimationComponent;

class FireObject :
    public GameObject
{
public:
    FireObject();
    virtual ~FireObject();

    AnimationComponent* m_pAnimationComponent;
    BoxCollider* m_pBoxCollider;
    bool m_bEnter = false;
    bool m_bIsAble = true;

private:
    float m_distance;

public:
    virtual bool Initialize() override;
    virtual void Update(float dt) override;
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;

   

    BoxCollider* GetBoxCollider() { return m_pBoxCollider; }
    void SetRadius(float r) { m_distance = r; }
};

