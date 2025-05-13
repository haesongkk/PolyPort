#pragma once
#include <afxwin.h>
class ColliderWindow : public CDialog
{
    DECLARE_DYNAMIC(ColliderWindow)

public:
    ColliderWindow();
    virtual ~ColliderWindow();

public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:

    DECLARE_MESSAGE_MAP()
};

