#pragma once
#include "BitmapComponent.h"
#include "BoxCollider.h"
#include "GameObject.h"

class SpikeObject :
    public GameObject
{
public:
    SpikeObject();
    virtual ~SpikeObject() override;

public:
    virtual bool Initialize() override;
    virtual void Update(float dt) override;

    void OnCollisionEnter(Collider& other) override;
    BoxCollider* m_pBoxCollider;
    BitmapComponent* m_pBitmapComponent;
};

