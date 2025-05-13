#include "pch.h"
#include "ColliderButton.h"
#include "ToolManager.h"

IMPLEMENT_DYNAMIC(ColliderButton, CButton)

BEGIN_MESSAGE_MAP(ColliderButton, CButton)
    ON_CONTROL_REFLECT(BN_CLICKED, OnButtonClicked)
END_MESSAGE_MAP()

void ColliderButton::OnButtonClicked()
{
    ToolManager::GetInst()->SetCurColliderKey(m_colliderType);
}

void ColliderButton::SetColliderTag(std::wstring _colliderTag)
{
    m_colliderType = _colliderTag;
}

std::wstring ColliderButton::GetCollideTag()
{
    return m_colliderType;
}
