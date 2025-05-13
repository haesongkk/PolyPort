#pragma once
#include "Component.h"


class GameObject;
class TransformComponent :
    public Component
{
public:

protected:
    TransformComponent* m_pParentComponent; // 부모 컴포넌트의 주소

    Vector2D m_relativeScale; // 상대 크기
    float m_relativeRotation; // 상대 회전
    Vector2D m_relativeTranslation; // 상대 위치

    D2D1_MATRIX_3X2_F m_relativeTransform; // 이 오브젝트만의 트랜스폼
    D2D1_MATRIX_3X2_F m_worldTransform; // 최종적인 트랜스폼

public:
    TransformComponent(GameObject* pOwner, string Name, TransformComponent* pRoot);
    virtual ~TransformComponent() override;

    virtual bool Initialize() override;
    virtual void Update(float dt) override;

    void SetRelativeScale(const Vector2D& obj) { m_relativeScale = obj; }
    Vector2D& GetRelativeScale() { return m_relativeScale; }
    void AddRelativeScale(const Vector2D& obj) { m_relativeScale += obj; }

    void SetRelativeRotation(const float degree) { m_relativeRotation = degree; }
    float& GetRelativeRotation() { return m_relativeRotation; }
    void AddRelativeRotation(const float degree) { m_relativeRotation += degree; }

    void SetRelativeTranslation(const Vector2D& obj) { m_relativeTranslation = obj; }
    Vector2D& GetRelativeTranslation() { return m_relativeTranslation; }
    void AddRelativeTranslation(const Vector2D& obj) { m_relativeTranslation += obj; }

    void SetParentTransform(TransformComponent* pParent) { m_pParentComponent = pParent; }
    TransformComponent* GetParentTransform() const { return m_pParentComponent; }

    D2D1_MATRIX_3X2_F& GetWorldTransform() { return m_worldTransform; }
    void SetWorldTransform(const D2D1_MATRIX_3X2_F& matrix) { m_worldTransform = matrix; }
};

