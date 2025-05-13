#include "pch.h"
#include "SaveWindow.h"
#include "MainWin.h"

IMPLEMENT_DYNAMIC(SaveWindow, CDialog)

BEGIN_MESSAGE_MAP(SaveWindow, CDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()

SaveWindow::SaveWindow(MainWin* _pMain)
	: CDialog(), m_pMain(_pMain)
{
}

int SaveWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_pFilePath = new CEdit;
	m_pFilePath->Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER, CRect(10,10,300,30), this, 0);
	m_pFilePath->SetWindowTextW(L"../Resource/default.json");
	return 0;
}

void SaveWindow::OnOK()
{
	UpdateData(TRUE);
	CString cFilePath;
	m_pFilePath->GetWindowText(cFilePath);
	std::wstring wFilePath;
	wFilePath = cFilePath.GetString();

	m_pMain->SaveData(wFilePath);
	CDialog::OnOK();

	delete this;

}

