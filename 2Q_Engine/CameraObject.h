#pragma once
#include "BoxCollider.h"
#include "BoxComponent.h"
#include "GameObject.h"

class CameraComponent;
class MovementComponent;
class RigidBody;
class CameraObject :
    public GameObject
{
public:
    CameraObject();
    virtual ~CameraObject() final;

    virtual void Update(float dt) final;
    virtual bool Initialize() final;

private:
    CameraComponent* m_pCameraComponent;
    RigidBody* m_pRigidBody;
    MovementComponent* m_pMovementComponent;
    GameObject* m_focusingObject;
    BoxComponent* m_pBoxComponent;
    BoxCollider* m_pBoxCollider;

public:
    void SetFocusingObject(GameObject* object) { m_focusingObject = object; }
    GameObject* GetFocusingObject() const { return m_focusingObject; }
    BoxCollider* GetBoxCollider() const { return m_pBoxCollider; }
};

