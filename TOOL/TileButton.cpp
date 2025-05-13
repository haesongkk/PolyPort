#include "pch.h"
#include "TileButton.h"

#include "ToolManager.h"

IMPLEMENT_DYNAMIC(TileButton, CButton)

BEGIN_MESSAGE_MAP(TileButton, CButton)
    ON_WM_CREATE()
    ON_WM_PAINT()
    ON_CONTROL_REFLECT(BN_CLICKED, OnButtonClicked)
END_MESSAGE_MAP()

int TileButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    m_pImage = new CImage;
    m_bIsCreated = true;
    return CButton::OnCreate(lpCreateStruct);
}

void TileButton::OnPaint()
{
    CPaintDC dc(this);

    m_pImage->Destroy();

    LPCTSTR str = m_tileTag.c_str();
    HRESULT hr = m_pImage->Load(str);
    if (hr != S_OK) return;

    m_pImage->Draw(dc, 0,0, TileSize, TileSize);


    return;
}

void TileButton::OnButtonClicked()
{
    Invalidate();

    CPaintDC dc(this);

    CRect rect;
    GetClientRect(&rect);
    dc.FillSolidRect(&rect, GetSysColor(COLOR_BTNFACE));

    m_pImage->Destroy();

    switch (ToolManager::GetInst()->GetMode())
    {
        case MODE::CreateImage:
        {
            m_tileTag = ToolManager::GetInst()->GetCurTileKey();
            break;
        }
        case MODE::DeleteImage:
        {
            m_tileTag = L"../Resource/tile/default.jpg";
            break;
        }
        case MODE::CreateCollider:
        {
            POINT tmp = ToolManager::GetInst()->GetColliderLeftTop();
            if (tmp.x == -1 && tmp.y == -1)
            {
                ToolManager::GetInst()->SetColliderLeftTop(m_tilePos);
            }
            else
            {
                m_leftTop = { tmp.x,tmp.y };
                ToolManager::GetInst()->SetColliderLeftTop({ -1,-1 });
            }
            break;
        }
        case MODE::DeleteCollider:
        {
            m_leftTop = { -1,-1 };
            break;
        }
    }
    

    LPCTSTR str = m_tileTag.c_str();
    HRESULT hr = m_pImage->Load(str);

    if (hr == S_OK)
        m_pImage->Draw(dc.m_hDC, 0, 0, TileSize, TileSize);

    UpdateWindow();

    return;
}

void TileButton::SetTilePos(POINT _tilePos)
{
    m_tilePos = _tilePos;
}

POINT TileButton::GetTilePos()
{
    return m_tilePos;
}

void TileButton::SetTileTag(std::wstring _tileTag)
{
    CPaintDC dc(this);

    m_pImage->Destroy();

    m_tileTag = _tileTag;
    LPCTSTR str = m_tileTag.c_str();
    HRESULT hr = m_pImage->Load(str);
    if (hr != S_OK) return;
    m_pImage->Draw(dc.m_hDC, 0, 0, TileSize, TileSize);

    Invalidate();
}

std::wstring TileButton::GetTileTag()
{
    return m_tileTag;
}

void TileButton::SetColliderLeftTop(POINT _lt)
{
    m_leftTop = { _lt.x,_lt.y };
}

POINT TileButton::GetColliderLeftTop()
{
    return m_leftTop;
}

bool TileButton::GetIsCreated()
{
    return m_bIsCreated;
}
