#pragma once
#include <afxwin.h>
class ColliderButton;
class ColliderPalette : public CDialog
{
    DECLARE_DYNAMIC(ColliderPalette)

public:
    ColliderPalette();
    virtual ~ColliderPalette();

public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:
    ColliderButton* m_pButtons;

    DECLARE_MESSAGE_MAP()
};

