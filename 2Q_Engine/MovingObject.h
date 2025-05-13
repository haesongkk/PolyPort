#pragma once
#include "GameObject.h"
class BoxCollider;
class BitmapComponent;

class MovingObject :
    public GameObject
{
public:
    MovingObject();
    virtual ~MovingObject();

public:
    BoxCollider* m_pBoxCollider;
    Vector2D m_route;
    float m_distance;

private:
    Vector2D m_startingPos;
    Vector2D m_endingPos;
public:
    virtual void Update(float dt) override;
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
    virtual bool Initialize() override;

    virtual void OnCollisionEnter(Collider& other) override;
    virtual void OnCollisionExit(Collider& other) override;

    void SetStartingPos(const Vector2D& vec) { m_startingPos = vec; }
    void SetEndingPos(const Vector2D& vec) { m_endingPos = vec; }

    void SetSize(int size);

    Vector2D GetStartingPos() const { return m_startingPos; }
    Vector2D GetEndingPos() const { return m_endingPos; }


};

