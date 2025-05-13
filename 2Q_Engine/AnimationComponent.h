#pragma once
#include "RenderComponent.h"
#include "AnimationAsset.h"


class AnimationComponent :
    public RenderComponent
{
private:
    int m_animationIndex;
    int m_curFrameIndex;
    int m_prevFrameIndex;
    bool m_bReverse;
    bool m_bLoop;
    float m_speed;
    float m_cumulativeTime;

    D2D1_RECT_F m_srcRect;
    D2D1_RECT_F m_destRect;
    AnimationAsset* m_pAnimationAsset; // 현재 에니메이션에셋
    AnimationInfo* m_pAnimationInfo; //현재 애니메이션 정보

public:
    AnimationComponent(GameObject* pOwner, string name, TransformComponent* pRoot );
    virtual ~AnimationComponent() final;

    virtual void Update(float dt) final;
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) final;
    virtual bool Initialize() final;

    void SetAnimationIndex(int idx) { m_animationIndex = idx; }
    void SetFrameIndex(int idx) { m_curFrameIndex = idx; }
    void SetReverse(bool b) { m_bReverse = b; }  
    void SetLoop(bool b) { m_bLoop = b; }
    void SetSpeed(float speed) { m_speed = speed; }

    int GetAnimationIndex() const { return m_animationIndex; }
    bool GetIsReverse() const { return m_bReverse; }
    bool GetIsLoop() const { return m_bLoop; }
    float GetSpeed() const { return m_speed; }

    void SetAnimationAsset(const wstring& strAssetKey);
    void SetAnimation(const string& name,const bool mirror,const bool loop);

    AnimationAsset* GetAnimationAsset() const { return m_pAnimationAsset; }


};

