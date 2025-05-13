#include "pch.h"
#include "ColliderWindow.h"

IMPLEMENT_DYNAMIC(ColliderWindow, CDialog)

BEGIN_MESSAGE_MAP(ColliderWindow, CDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()

ColliderWindow::ColliderWindow()
{
}

ColliderWindow::~ColliderWindow()
{
}

int ColliderWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return 0;
}
