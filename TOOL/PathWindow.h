#pragma once
class PathWindow : public CDialog
{
    DECLARE_DYNAMIC(PathWindow)

public:
    PathWindow(CWnd* pParent = NULL); 
    virtual ~PathWindow();

public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

    DECLARE_MESSAGE_MAP()

private:
    CEdit* m_pPathEditBox;
};

