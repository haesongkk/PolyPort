#pragma once
#include "BoxCollider.h"
#include "GameObject.h"
class PartSceneObject :
    public GameObject
{
public:
    PartSceneObject();
    virtual ~PartSceneObject() override;

    void OnCollisionEnter(Collider& other) override;
    void OnCollisionExit(Collider& other) override;
    void OnCollisionStay(Collider& other) override;
    BoxCollider* m_pBoxCollider;
private:
};

