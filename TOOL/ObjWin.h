#pragma once
class CompWin;
class ObjWin : public CDialog
{
    DECLARE_DYNAMIC(ObjWin)

public:
    ObjWin(CWnd* pParent = NULL); 
    virtual ~ObjWin();

    CListCtrl m_ObjectList;
    CompWin* m_comp;


public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnCreateGameObject();
    afx_msg void OnSelectObject(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRenameObject(NMHDR* pNMHDR, LRESULT* pResult);

    DECLARE_MESSAGE_MAP()
};

