#include "pch.h"
#include "ButtonComponent.h"
#include "Input.h"
#include "GameObject.h"
#include "Event.h"
#include "World.h"
#include "Sound.h"
#include "Debug.h"
#include "ButtonObject.h"


ButtonComponent::ButtonComponent(GameObject* pOwner, const string name, TransformComponent* pRoot)
    :UIComponent(pOwner,name,pRoot)
{
    SetRelativeTranslation({ 960, 540 });
}


void ButtonComponent::Update(float dt)
{
    __super::Update(dt);

    if (m_pActiveBitmap == m_pDefaultBitmap) return;

    int x = Input::m_pInputInstance->GetRealMousePos().x;
    int y = Input::m_pInputInstance->GetRealMousePos().y;
    m_preOnButton = m_bOnButton;
    m_bOnButton =
        x > m_buttonRect.left
        && x < m_buttonRect.right
        && y > m_buttonRect.top
        && y < m_buttonRect.bottom;

    Vector2D button = { m_buttonRect.left - m_buttonRect.right, m_buttonRect.top - m_buttonRect.bottom };
    Vector2D pos = { (m_buttonRect.left + m_buttonRect.right) / 2,(m_buttonRect.top + m_buttonRect.bottom) / 2 };
    bool onClick = Input::m_pInputInstance->GetKeyState(KEY::LBUTTON) == KEY_STATE::TAP;

    if (m_bOnButton)
    {
        Debug::Rect(D2D1::Matrix3x2F::Translation(pos.x, pos.y), button, true);

        wstring wname;
        string name = m_pOwner->GetTag();
        wname.assign(name.begin(), name.end());
        Debug::Text(L"on " + wname);
        if(!m_preOnButton) Sound::Play(SFX, "../Resource/sound/UI_select.wav");

        if (onClick)
        {
            Debug::Log(wname + L" click");
            Sound::Play(SFX, "../Resource/sound/UI_click.wav");
            m_pOwner->OnButtonClick(m_pOwner->GetTag());
        }
    }
    else
    {
        Debug::Rect(D2D1::Matrix3x2F::Translation(pos.x, pos.y), button, false);
    }
}

void ButtonComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
    RenderComponent::Render(pRenderTarget);
    if (!m_bVisible) return;
    pRenderTarget->SetTransform(D2D1::IdentityMatrix());
    if(m_bOnButton) pRenderTarget->DrawBitmap(m_pActiveBitmap);
    else pRenderTarget->DrawBitmap(m_pDefaultBitmap);
}

void ButtonComponent::SetActiveBitmap(wstring _active)
{
    SetBitmap(_active);
    m_pActiveBitmap = m_pBitmap;
}

void ButtonComponent::SetDefaultBitmap(wstring _default)
{
    SetBitmap(_default);
    m_pDefaultBitmap = m_pBitmap;
}

void ButtonComponent::SetButtonRect(float x, float y, float dx, float dy)
{
    m_buttonRect.left = x - dx / 2;
    m_buttonRect.right = x + dx / 2;
    m_buttonRect.top = y - dy / 2;
    m_buttonRect.bottom = y + dy / 2;
}

