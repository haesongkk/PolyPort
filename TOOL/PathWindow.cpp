#include "pch.h"
#include "PathWindow.h"

#include "pch.h"
#include "TOOL.h"
#include "MainWin.h"


IMPLEMENT_DYNAMIC(PathWindow, CDialog)

BEGIN_MESSAGE_MAP(PathWindow, CDialog)
    ON_WM_CREATE()
END_MESSAGE_MAP()

PathWindow::PathWindow(CWnd* pParent)
    :CDialog(IDD_ABOUTBOX, pParent)
{
}

PathWindow::~PathWindow()
{
}

int PathWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    return 0;
}
