#include "pch.h"
#include "ColliderPalette.h"

#include "ColliderButton.h"


IMPLEMENT_DYNAMIC(ColliderPalette, CDialog)

BEGIN_MESSAGE_MAP(ColliderPalette, CDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()

ColliderPalette::ColliderPalette()
{
}

ColliderPalette::~ColliderPalette()
{
}

int ColliderPalette::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect btnRt = CRect(0, 0, 80, 30);

	m_pButtons = new ColliderButton[4];

	m_pButtons[0].Create(_T("Ground"), WS_CHILD | WS_VISIBLE | BS_USERBUTTON, btnRt, this, IDC_RADIO_TEXTURE);
	m_pButtons[0].SetColliderTag(L"Ground");
	btnRt.OffsetRect(0, 30);

	m_pButtons[1].Create(_T("Ladder"), WS_CHILD | WS_VISIBLE | BS_USERBUTTON, btnRt, this, IDC_RADIO_TEXTURE);
	m_pButtons[1].SetColliderTag(L"Ladder");

	btnRt.OffsetRect(0, 30);

	m_pButtons[2].Create(_T("LeftTop"), WS_CHILD | WS_VISIBLE | BS_USERBUTTON, btnRt, this, IDC_RADIO_TEXTURE);
	m_pButtons[2].SetColliderTag(L"LeftTop");
	btnRt.OffsetRect(0, 30);
	
	m_pButtons[3].Create(_T("RightTop"), WS_CHILD | WS_VISIBLE | BS_USERBUTTON, btnRt, this, IDC_RADIO_TEXTURE);
	m_pButtons[3].SetColliderTag(L"RightTop");


	return 0;
}
