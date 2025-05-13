#pragma once
#include "TransformComponent.h"
class CameraComponent :
    public TransformComponent
{
public:
    CameraComponent(GameObject* pOwner, string name, TransformComponent* pRoot);
    virtual ~CameraComponent() override;

private:
    D2D1_MATRIX_3X2_F m_inversedTransform;
    GameObject* m_focusingObject;
    D2D1_MATRIX_3X2_F m_backupTransform;
    int m_left = 0;
    int m_right = 0;
    int m_top = 0;
    int m_bottom = 0;

public:
    virtual void Update(float dt) override;
    virtual bool Initialize() override;

    D2D1_MATRIX_3X2_F GetInversedTransform()
    {
        return m_inversedTransform;
    }
};

