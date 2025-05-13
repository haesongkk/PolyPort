#include "pch.h"
#include "ImageButton.h"
#include "ToolManager.h"

#include <afxstr.h>

IMPLEMENT_DYNAMIC(ImageButton, CButton)

BEGIN_MESSAGE_MAP(ImageButton, CButton)
    ON_WM_PAINT()
    ON_CONTROL_REFLECT(BN_CLICKED, &ImageButton::OnButtonClicked)
END_MESSAGE_MAP()


void ImageButton::OnPaint()
{
    CPaintDC dc(this);

    LPCTSTR str = m_tileTag.c_str();

    m_pImage = new CImage;
    m_pImage->Destroy();
    m_pImage->Load(str);
    m_pImage->Draw(dc.m_hDC, 0, 0, 80, 80);

    return;
}

void ImageButton::OnButtonClicked()
{
    ToolManager::GetInst()->SetCurTileKey(m_tileTag);
    ToolManager::GetInst()->SetMode(MODE::CreateImage);
}

void ImageButton::SetTileTag(std::wstring _tileTag)
{
    m_tileTag = _tileTag;
}

