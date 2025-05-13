#pragma once
#include "Collider.h"

class BoxCollider :
    public Collider
{
protected:

    vector<Vector2D> m_vertex = { {0,0},{0,0} ,{0,0} ,{0,0} };
    //�浹 Ȯ���� ���� �ӽ÷� �� �߰�
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

