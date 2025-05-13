#pragma once
#include "BoxComponent.h"
#include "EllipseComponent.h"
#include "FSMComponent.h"
#include "GameObject.h"

class FireObject;
class FSMCharacter;
class AnimationComponent;
class BoxCollider;
class EllipseComponent;
class BubbleObject :
    public GameObject
{
public:
    BubbleObject();
    virtual ~BubbleObject() override;

private:
    BoxCollider* m_pBoxCollider;
    AnimationComponent* m_pAnimationComponent;
    FSMCharacter* m_pFSMCharacter;
    FSMComponent* m_pFSMComponent;
    FireObject* m_pFireobject;

    bool m_bIsActive = true; // 현재 오브젝트가 존재하는 지
    bool m_bInteract = false; // 현재 오브젝트가 Player와 상호작용하고 있는 지

    float m_elapsedTime = 0.f;
    float m_radius = 100.f;
    float m_activationTimer;

public:
    void OnCollisionEnter(Collider& other) override;
    void OnCollisionExit(Collider& other) override;

    virtual bool Initialize() override;
    virtual void Update(float dt) override;
    virtual void LateUpdate(float dt);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;

    void AnimationEnd() const;

    void SetRadius(float r) { m_radius = r; }
    float GetRadius() const { return m_radius; }

    FireObject* GetFireObject() const { return m_pFireobject; }
};



