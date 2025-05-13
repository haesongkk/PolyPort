#pragma once
#include "Collider.h"

class BoxCollider :
    public Collider
{
protected:

    vector<Vector2D> m_vertex = { {0,0},{0,0} ,{0,0} ,{0,0} };
    //충돌 확인을 위해 임시로 색 추가
    COLORREF m_color;

public:
    Vector2D m_widthVector;
    Vector2D m_heightVector;
    BoxCollider(GameObject* pOwner, string Name, TransformComponent* pRoot);
    ~BoxCollider();
    virtual void Update(float dt) override;
    
    ColliderType GetColliderType() { return m_colliderType; }
    void SetAxis();

    void SetVertex();
    vector<Vector2D>& GetVertex() { return m_vertex; }

};

