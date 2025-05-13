#include "pch.h"
#include "ObjWin.h"

#include "pch.h"
#include "TOOL.h"
#include "MainWin.h"
#include "TempProcess.h"
#include "CompWin.h"


IMPLEMENT_DYNAMIC(ObjWin, CDialog)

BEGIN_MESSAGE_MAP(ObjWin, CDialog)
    ON_WM_CREATE()
    ON_CONTROL(BN_CLICKED, ID_CREATE_GAMEOBJECT_BUTTON, ObjWin::OnCreateGameObject)
    ON_NOTIFY(NM_CLICK, IDC_OBJECT_LIST, ObjWin::OnSelectObject)
    ON_NOTIFY(NM_RCLICK, IDC_OBJECT_LIST, ObjWin::OnRenameObject)
END_MESSAGE_MAP()

ObjWin::ObjWin(CWnd* pParent)
    :CDialog(IDD_ABOUTBOX, pParent)
{
}

ObjWin::~ObjWin()
{
}

int ObjWin::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    // 버튼 생성
    CRect buttonRect(10, 10, 120, 40);
    CButton* pCreateButton = new CButton;
    pCreateButton->Create(_T("Create"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, buttonRect, this, ID_CREATE_GAMEOBJECT_BUTTON);

    // 리스트 컨트롤 생성
    CRect listRect(10, 50, 200, 250);
    m_ObjectList.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL, listRect, this, IDC_OBJECT_LIST);

    // 리스트 컬럼 추가
    m_ObjectList.InsertColumn(0, _T("GameObject Name"), LVCFMT_LEFT, 150);

    //for (int i = 0; i < g_process->GetObjCount(); i++)
    //{
    //    // tag를 받아와서 형변환
    //    std::string sTag = g_process->GetTag(i);
    //    CString cTag(sTag.c_str());

    //    m_ObjectList.InsertItem(i, cTag);
    //}
    return 0;
}

void ObjWin::OnCreateGameObject()
{
    // 오브젝트 추가
    int itemIndex = m_ObjectList.GetItemCount();
    CString newItemName;
    newItemName.Format(_T("New GameObject %d"), itemIndex);

    m_ObjectList.InsertItem(itemIndex, newItemName);
    std::string tag = std::string(CT2CA(newItemName));
    //g_process->CreateObject(tag);

}

void ObjWin::OnSelectObject(NMHDR* pNMHDR, LRESULT* pResult)
{
    // 선택한 항목 cast
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    // 선택된 항목 인덱스 얻기
    int selectedIndex = pNMLV->iItem;

    if (selectedIndex == -1) return;
    //if (selectedIndex >= g_process->GetObjCount()) return;

    // 선택된 항목의 내용 얻기
    CString itemName = m_ObjectList.GetItemText(selectedIndex, 0);

    if (m_comp)
    {
        m_comp->DestroyWindow();
        delete m_comp;
    }

    // 컴포넌트 다이얼로그 생성
    m_comp = new CompWin(itemName);
    m_comp->Create(IDD_ABOUTBOX, this);
    m_comp->SetWindowText(itemName);
    m_comp->SetWindowPos(NULL, 0, 300, 250, 600, SWP_SHOWWINDOW);

    *pResult = 0;
}

void ObjWin::OnRenameObject(NMHDR* pNMHDR, LRESULT* pResult)
{
    // 선택된 항목의 인덱스 불러오기
    int selectedIndex = m_ObjectList.GetNextItem(-1, LVNI_SELECTED);
    if (selectedIndex == -1) return;
    //if (selectedIndex >= g_process->GetObjCount()) return;
    // input box 띄우기
    //InputBox inputBox;

    // 확인 눌렀을 경우
    //if (inputBox.DoModal() == IDOK)
    //{
    //    // 기존 이름 불러오기
    //    const int bufferSize = 256;
    //    TCHAR buffer[bufferSize];
    //    CString oldName;
    //    m_ObjectList.GetItemText(selectedIndex, 0, buffer, bufferSize);
    //    oldName = buffer;

    //    // 입력된 새로운 이름 불러오기
    //    CString newName = inputBox.m_inputText;

    //    // 항목 이름 변경
    //    m_ObjectList.SetItemText(selectedIndex, 0, newName);

    //    // 문자열 형식 변환
    //    CT2CA old(oldName);
    //    CT2CA _new(newName);
    //    std::string oldStr(old);
    //    std::string newStr(_new);

    //    // 게임 오브젝트 이름 변경
    //    g_app->SetName(oldStr, newStr);
    //}
}



