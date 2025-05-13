#include "pch.h"
#include "D2DRenderer.h"
#include "AnimationAsset.h"

AnimationAsset::AnimationAsset()
	: m_animations()
	, m_pBitmap(nullptr)
{
}

AnimationAsset::~AnimationAsset()
{
	// ∫Ò∆Æ∏  Release

}

void AnimationAsset::SetBitmap(ID2D1Bitmap* pBitmap)
{
	m_pBitmap = pBitmap;
}

AnimationInfo* AnimationAsset::GetAnimationInfo(const string animationName)
{
	for (size_t i = 0; i < m_animations.size(); i++)
	{
		if (m_animations[i].m_name == animationName)
		{
			return &m_animations[i];
		}
	}
	return nullptr;
}

