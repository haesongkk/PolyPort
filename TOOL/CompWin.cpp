#include "pch.h"
#include "CompWin.h"

#include "TOOL.h"
#include "TempProcess.h"
#include "MainWin.h"

#define TransTextRect CRect(10, 10, 150, 30)
#define TransEditRect CRect(10, 35, 40, 55)
#define TransEditOffSetX 40

#define RenderButtonRect CRect(10, 100, 30, 120)
#define RenderTextRect CRect(35, 100, 200, 120)
#define RenderRectOffSetY 25

#define CompButtonRect CRect(10, 150, 30, 170)
#define CompTextRect CRect(35, 150, 200, 170)
#define CompRectOffsetY 25

enum TRANSINFO
{
	POSX, POSY, ROTATE, SCALEX, SCALEY, TEND,
};

enum COMPONENT
{
	ANIMATOR, COLLIDER, LOGIC, CEND,
};



IMPLEMENT_DYNAMIC(CompWin, CDialog)

BEGIN_MESSAGE_MAP(CompWin, CDialog)
	ON_WM_CREATE()
	//ON_CONTROL(BN_CLICKED, ID_ASSIGN_BUTTON, CompWin::OnAssign)
END_MESSAGE_MAP()


CompWin::CompWin(CString _name)
	:CDialog(IDD_ABOUTBOX)
{
	SetName(_name);

	m_pTextTransform = new CStatic;
	m_pEditTransform = new CEdit[TRANSINFO::TEND];

	m_pAssignButton = new CButton;

	m_pRadioButton = new CButton[2];
	m_pRadioText = new CStatic[2];

	m_pCheckButton = new CButton[COMPONENT::CEND];
	m_pCheckText = new CStatic[COMPONENT::CEND];

	m_compTags =
	{
		L"animator",L"collider",L"Logic",
	};
	m_compIDs =
	{
		IDC_CHECK_ANIMATOR,
		IDC_CHECK_COLLIDER,
		IDC_CHECK_LOGIC,
	};
}

CompWin::~CompWin()
{
	delete m_pTextTransform;
	delete[] m_pEditTransform;

	delete m_pAssignButton;

	delete[] m_pRadioButton;
	delete[] m_pRadioText;

	delete[] m_pCheckButton;
	delete[] m_pCheckText;
}

void CompWin::SetName(CString _name)
{
	CT2CA tmp(_name);
	m_objTag = tmp;
}

int CompWin::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	TransCtr();
	RenderCtr();
	CompCtr();
	return 0;
}

void CompWin::OnAssign()
{
}

void CompWin::TransCtr()
{
	// text 생성
	m_pTextTransform->Create(_T("transform"), WS_CHILD | WS_VISIBLE | SS_LEFT, TransTextRect, this);

	// editor 생성
	CRect editRect = TransEditRect;
	for (int i = 0; i < TRANSINFO::TEND; i++)
	{
		m_pEditTransform[i].Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER, editRect, this, 0);

		editRect.OffsetRect(TransEditOffSetX, 0);
	}

	// 나중에 오브젝트의 값 직접 받아오기
	double transformInfo[TRANSINFO::TEND];
	transformInfo[TRANSINFO::POSX] = 0;
	transformInfo[TRANSINFO::POSY] = 0;
	transformInfo[TRANSINFO::ROTATE] = 0;
	transformInfo[TRANSINFO::SCALEX] = 0;
	transformInfo[TRANSINFO::SCALEY] = 0;

	// 초기값 입력
	for (int i = 0; i <= TRANSINFO::ROTATE; i++)
	{
		LPWSTR str = CastDtoS_DOWN(transformInfo[i]);
		m_pEditTransform[i].SetWindowTextW(str);
	}
	for (int i = TRANSINFO::SCALEX; i < TRANSINFO::TEND; i++)
	{
		LPWSTR str = CastDtoS(transformInfo[i]);
		m_pEditTransform[i].SetWindowTextW(str);
	}

}

void CompWin::RenderCtr()
{
	CRect radioRect = RenderButtonRect;
	CRect textRect = RenderTextRect;

	// Texture
	m_pRadioButton[0].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, radioRect, this, IDC_RADIO_TEXTURE);
	m_pRadioText[0].Create(_T("Image"), WS_CHILD | WS_VISIBLE | SS_LEFT, textRect, this, IDC_RADIO_TEXTURE);

	radioRect.OffsetRect(0, RenderRectOffSetY);
	textRect.OffsetRect(0, RenderRectOffSetY);

	// Text
	m_pRadioButton[1].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, radioRect, this, IDC_RADIO_TEXT);
	m_pRadioText[1].Create(_T("Text"), WS_CHILD | WS_VISIBLE | SS_LEFT, textRect, this, IDC_RADIO_TEXT);

	// 초기값은 나중에 렌더 컴포넌트 받아와서 
	m_pRadioButton[0].SetCheck(BST_CHECKED);
}

void CompWin::CompCtr()
{
	CRect checkRect = CompButtonRect;
	CRect textRect = CompTextRect;

	for (int i = 0; i < COMPONENT::CEND; i++)
	{
		m_pCheckButton[i].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, checkRect, this, m_compIDs[i]);
		m_pCheckText[i].Create(m_compTags[i], WS_CHILD | WS_VISIBLE | SS_LEFT, textRect, this, m_compIDs[i]);

		checkRect.OffsetRect(0, CompRectOffsetY);
		textRect.OffsetRect(0, CompRectOffsetY);
	}
}

LPWSTR CompWin::CastDtoS(double _d)
{
	TCHAR str[32];
	_sntprintf_s(str, _countof(str), _T("%.1f"), _d);
	return str;
}

LPWSTR CompWin::CastDtoS_DOWN(double _d)
{
	TCHAR str[32];
	_sntprintf_s(str, _countof(str), _T("%.0f"), _d);
	return str;
}
