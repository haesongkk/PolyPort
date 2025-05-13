#include "pch.h"

#include "AnimationComponent.h"
#include "FSMCharacter.h"
#include "D2DRenderer.h"
#include "RenderComponent.h"
#include "AnimationAsset.h"
#include "BubbleObject.h"
#include "PlayerObject.h"
#include "World.h"

AnimationComponent::AnimationComponent(GameObject* pOwner, string name, TransformComponent* pRoot)
	: RenderComponent(pOwner, name, pRoot)
	, m_animationIndex(0)
	, m_curFrameIndex(0)
	, m_prevFrameIndex(0)
	, m_bLoop(true)
	, m_bReverse(false)
	, m_pAnimationAsset(nullptr)
	, m_pAnimationInfo(nullptr)
	, m_speed(1.f)
	, m_cumulativeTime(0.f)
{
	m_destRect = { 0.f,0.f,0.f,0.f };
	m_srcRect = { 0.f,0.f,0.f,0.f };
}

AnimationComponent::~AnimationComponent()
{
	D2DRenderer::m_instance->ReleaseAnimationAsset(m_pAnimationAsset);
}

void AnimationComponent::Update(float dt)
{
	__super::Update(dt);

	assert(m_pAnimationAsset != nullptr);

	if (m_pAnimationInfo == nullptr)
		return;

	//애니메이션 프레임 인덱스관련 업데이트
	const float progressTime = m_pAnimationInfo->progressTime;

	m_prevFrameIndex = m_curFrameIndex;
	m_cumulativeTime += dt * m_speed;
	if (m_cumulativeTime >= progressTime)
	{
		m_cumulativeTime = 0;
		m_curFrameIndex++;
		if (m_bLoop)
		{
			m_curFrameIndex = m_curFrameIndex % m_pAnimationInfo->m_frames.size();
		}
		else
		{
			if(m_curFrameIndex > m_pAnimationInfo->m_frames.size() - 1)
			{
				m_curFrameIndex = m_pAnimationInfo->m_frames.size() - 1;
				if(dynamic_cast<PlayerObject*>(m_pOwner) != nullptr)
					dynamic_cast<PlayerObject*>(m_pOwner)->AnimationEnd();
				else if(dynamic_cast<BubbleObject*>(m_pOwner) != nullptr)
					dynamic_cast<BubbleObject*>(m_pOwner)->AnimationEnd();
			}
		}
	}

	//애니메이션 Transform 업데이트
	m_worldTransform = m_relativeTransform;
	
	if (m_bReverse == true)
	{
		m_worldTransform = m_worldTransform * D2D1::Matrix3x2F::Scale(-1.f, 1.f);
	}

	m_worldTransform = m_worldTransform * m_pParentComponent->GetWorldTransform();

	// 애니메이션 RECT 업데이트
	if (m_pAnimationInfo == nullptr)
		return;

	m_srcRect = m_pAnimationInfo->m_frames[m_curFrameIndex].rect;
	m_destRect = { -(m_srcRect.right - m_srcRect.left) / 2
				 , -(m_srcRect.bottom - m_srcRect.top) / 2
				 , (m_srcRect.right - m_srcRect.left) / 2
				 , (m_srcRect.bottom - m_srcRect.top) / 2 };


}

void AnimationComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	if (m_pAnimationInfo == nullptr)
		return;

	__super::Render(pRenderTarget);

	if(m_bVisible)
	{
		pRenderTarget->DrawBitmap(m_pAnimationAsset->GetBitmap(), m_destRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_srcRect);
	}
}

bool AnimationComponent::Initialize()
{
	return false;
}

void AnimationComponent::SetAnimationAsset(const wstring& strAssetKey)
{
	m_pAnimationAsset = D2DRenderer::m_instance->CreateAnimationAssetFromFile(strAssetKey);
}

void AnimationComponent::SetAnimation(const string& name,const bool mirror,const bool loop)
{
	m_bLoop = loop;
	m_bReverse = mirror;
	m_pAnimationInfo = m_pAnimationAsset->GetAnimationInfo(name);
	assert(m_pAnimationInfo != nullptr, "Animation Info is nullptr");
}
