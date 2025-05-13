#include "pch.h"
#include "framework.h"

#include "TOOL.h"
#include "MainWin.h"

TOOL theApp;

BEGIN_MESSAGE_MAP(TOOL, CWinAppEx)
END_MESSAGE_MAP()

TOOL::TOOL() noexcept
{
}

BOOL TOOL::InitInstance()
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();

    if (!AfxOleInit())
    {
        AfxMessageBox(IDP_OLE_INIT_FAILED);
        return FALSE;
    }
    AfxEnableControlContainer();
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));
    LoadStdProfileSettings(4);

    MainWin* pMainWin = new MainWin;
    if (!pMainWin || !pMainWin->LoadFrame(IDR_MAINFRAME))
    {
        delete pMainWin;
        return FALSE;
    }
    m_pMainWnd = pMainWin;

    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    HWND hWnd = pMainWin->GetSafeHwnd();
    SetWindowPos(hWnd, nullptr, 0, 0, WindowWidth, WindowHeight, SWP_NOZORDER);

    pMainWin->ShowWindow(m_nCmdShow);
    pMainWin->UpdateWindow();

    return TRUE;
}