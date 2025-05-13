#include "pch.h"
#include "NewWindow.h"

#include "MainWin.h"

IMPLEMENT_DYNAMIC(NewWindow, CDialog)

BEGIN_MESSAGE_MAP(NewWindow, CDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()

NewWindow::NewWindow(MainWin* _pMain)
	: CDialog(), m_pMain(_pMain)
{
}

int NewWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// 가로 타일 수 입력 창
	m_pTileWidth = new CEdit;
	m_pTileWidth->Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER, CRect(10, 10, 50, 30), this, 0);
	m_pTileWidth->SetWindowTextW(L"40");

	// 세로 타일 수 입력 창
	m_pTileHeight = new CEdit;
	m_pTileHeight->Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER, CRect(60, 10, 100, 30), this, 0);
	m_pTileHeight->SetWindowTextW(L"23");

	return 0;
}

void NewWindow::OnOK()
{
	UpdateData(TRUE);

	CString cTileWitdh, cTileHeight;
	int iTileWidth, iTileHeight;

	m_pTileWidth->GetWindowText(cTileWitdh);
	m_pTileHeight->GetWindowText(cTileHeight);

	iTileWidth = _tstoi(cTileWitdh);
	iTileHeight = _tstoi(cTileHeight);

	m_pMain->NewData(iTileWidth, iTileHeight);

	CDialog::OnOK();

	delete this;
}
