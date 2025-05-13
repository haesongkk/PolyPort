#pragma once
#include "GameObject.h"
#include "TransformComponent.h"

class RenderComponent :
    public TransformComponent
{
public:
    RenderComponent(GameObject* pOwner, const string& Name, TransformComponent* pRoot);
    virtual ~RenderComponent() override;

protected:
    int m_renderingOrder; // �׸��� ����
    bool m_bVisible; // �׷��� �ϴ� ��(ī�޶� ���)

public:
    void SetRenderingOrder(int Order) { m_renderingOrder = Order; }
    int GetRenderingOrder() { return m_renderingOrder; }
    void SetVisible(bool Visible) { m_bVisible = Visible; }
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Update(float dt) override
    {
	    __super::Update(dt);
        m_bVisible = m_pOwner->IsVisible();
    }
    virtual bool Initialize() override { return true; }

    bool GetVisible() { return m_bVisible; }
};
