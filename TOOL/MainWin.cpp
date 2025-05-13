#include "pch.h"
#include "MainWin.h"

#include "TOOL.h"

#include "TileButton.h"
#include "ImagePalette.h"

#include "SaveWindow.h"
#include "LoadWindow.h"
#include "NewWindow.h"

#include "ToolManager.h"

#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


IMPLEMENT_DYNAMIC(MainWin, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(MainWin, CMDIFrameWnd)
    ON_WM_CREATE()
    ON_COMMAND(ID_FILE_NEW, &OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &OnFileOpen)
    ON_COMMAND(ID_FILE_SAVE, &OnFileSave)
END_MESSAGE_MAP()

MainWin::MainWin() noexcept
{
}

MainWin::~MainWin()
{
    for (int i = 0; i < MaxTileMapHeight; i++)
        delete[] m_pTiles[i];
    delete[] m_pTiles;
}

BOOL MainWin::PreCreateWindow(CREATESTRUCT& cs)
{
    return CMDIFrameWnd::PreCreateWindow(cs);
}

BOOL MainWin::PreTranslateMessage(MSG* _pMsg)
{
    const int space = 1000;

    if (_pMsg->message == WM_KEYDOWN)
    {
        Invalidate();

        CPaintDC dc(this);

        if (_pMsg->wParam == 'X')
        {
            ToolManager::GetInst()->SetMode(MODE::DeleteImage);
            return 0;
        }
#ifdef _DEBUG
        if (_pMsg->wParam == 'C')
        {
            ToolManager::GetInst()->SetMode(MODE::CreateCollider);
            ToolManager::GetInst()->SetColliderLeftTop({ -1,-1 });
            return 0;
        }
        if (_pMsg->wParam == 'V')
        {
            for (int i = 0; i < MaxTileMapHeight; i++)
            {
                for (int j = 0; j < MaxTileMapWidth; j++)
                {
                    if (!m_pTiles[j][i].GetIsCreated()) continue;

                    POINT lt, rb;
                    lt.x = m_pTiles[j][i].GetColliderLeftTop().x;
                    lt.y = m_pTiles[j][i].GetColliderLeftTop().y;
                    rb.x = m_pTiles[j][i].GetTilePos().x;
                    rb.y = m_pTiles[j][i].GetTilePos().y;
                    if (lt.x == -1 && lt.y == -1) continue;
                    
                    CRect rt(lt.x*TileSize, lt.y * TileSize, rb.x * TileSize + TileSize, rb.y * TileSize + TileSize);
                    rt.top += btnRt.top;
                    rt.bottom += btnRt.top;
                    rt.left += btnRt.left;
                    rt.right += btnRt.left;

                    dc.FillSolidRect(&rt, GetSysColor(COLOR_BTNFACE));
                }
            }
            ToolManager::GetInst()->SetMode(MODE::DeleteCollider);
            return 0;

        }
#endif

        if(_pMsg->wParam == 'W')
            btnRt.OffsetRect(0, space/2);
        else if(_pMsg->wParam == 'A')
            btnRt.OffsetRect(space, 0);
        else if(_pMsg->wParam == 'S')
            btnRt.OffsetRect(0, -space/2);
        else if (_pMsg->wParam == 'D')
            btnRt.OffsetRect(-space, 0);
        else return 0;
        
        CRect rect;
        GetClientRect(&rect);
        dc.FillSolidRect(&rect, GetSysColor(COLOR_BTNFACE));

        CRect tmp = btnRt;
        int count = 0;
        for (int i = 0; i < MaxTileMapHeight; i++)
        {
            for (int j = 0; j < MaxTileMapWidth; j++)
            {
                if (m_pTiles[j][i].GetIsCreated())
                {
                    m_pTiles[j][i].MoveWindow(tmp);
                    tmp.OffsetRect(TileSize, 0);
                    count++;
                }
            }
            tmp.OffsetRect(0, TileSize);
            tmp.OffsetRect(-TileSize * count, 0);
            count = 0;
        }

        UpdateWindow();
    }
        
    return 0;
}

int MainWin::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    // 이미지 팔레트 생성
    m_pPalette = new ImagePalette;
    m_pPalette->Create(IDD_ABOUTBOX, this);
    m_pPalette->SetWindowText(_T("image"));
    m_pPalette->SetWindowPos(NULL, 0, WindowHeight - 400, WindowWidth, 400, SWP_SHOWWINDOW);

    // 타일 맵 동적 할당
    m_pTiles = new TileButton * [MaxTileMapWidth];
    for (int i = 0; i < MaxTileMapWidth; i++)
        m_pTiles[i] = new TileButton[MaxTileMapHeight];

    return 0;
}

void MainWin::AddCollider(POINT _lt, POINT _rb)
{
    CRect rt(_lt.x, _lt.y, _rb.x, _rb.y);
    m_colliders.push_back(rt);
}

void MainWin::OnFileNew()
{
    // 새로 만들기 눌렀을 경우
    // 메모리 해제는 OnOk에서
    m_pNewWindow = new NewWindow(this);
    m_pNewWindow->Create(IDD_ABOUTBOX, this);
    m_pNewWindow->SetWindowText(_T("new"));
    m_pNewWindow->SetWindowPos(NULL, 300, 300, 500, 100, SWP_SHOWWINDOW);
}

void MainWin::OnFileOpen()
{
    // 열기 눌렀을 경우
    // 메모리 해제는 OnOk에서
    m_pLoadWindow = new LoadWindow(this);
    m_pLoadWindow->Create(IDD_ABOUTBOX, this);
    m_pLoadWindow->SetWindowText(_T("load"));
    m_pLoadWindow->SetWindowPos(NULL, 300, 300, 500, 100, SWP_SHOWWINDOW);
}

void MainWin::OnFileSave()
{
    // 저장 눌렀을 경우
    // 메모리 해제는 OnOk에서
    m_pSaveWindow = new SaveWindow(this);
    m_pSaveWindow->Create(IDD_ABOUTBOX, this);
    m_pSaveWindow->SetWindowText(_T("save"));
    m_pSaveWindow->SetWindowPos(NULL, 300,300,500,100, SWP_SHOWWINDOW);
}

void MainWin::SaveData(std::wstring _filePath)
{
    json world_data;
    for (int i = 0; i < MaxTileMapHeight; i++)
    {
        for (int j = 0; j < MaxTileMapWidth; j++)
        {
            // 생성되지 않았다면 저장하지 않음
            if (!m_pTiles[j][i].GetIsCreated())continue;

            std::wstring btag = m_pTiles[j][i].GetTileTag();
            //if (btag == L"" || btag == L"../Resource/tile/default.jpg") continue;

            json obj_data;
            obj_data["tileImage"] =
            {
                 CastWstr(btag),
                 m_pTiles[j][i].GetTilePos().x,
                 m_pTiles[j][i].GetTilePos().y
            };

            POINT tmp = m_pTiles[j][i].GetColliderLeftTop();
            if (tmp.x != -1 && tmp.y != -1)
            {
                obj_data["tileCollider"] =
                {
                    tmp.x, tmp.y,
                    m_pTiles[j][i].GetTilePos().x,
                    m_pTiles[j][i].GetTilePos().y
                };
            }
            world_data.push_back(obj_data);
        }
    }

    std::ofstream file{ _filePath };
    assert(file.is_open());

    file << world_data.dump(2);
    file.close();
}

void MainWin::LoadData(std::wstring _filePath)
{
    for (int i = 0; i < MaxTileMapHeight; i++)
        delete[] m_pTiles[i];
    delete[] m_pTiles;

    m_pTiles = new TileButton * [MaxTileMapWidth];
    for (int i = 0; i < MaxTileMapWidth; i++)
        m_pTiles[i] = new TileButton[MaxTileMapHeight];

    std::ifstream file(_filePath);
    assert(file.is_open());

    json world_data;
    file >> world_data;

    for (const auto& obj_data : world_data)
    {
        if (obj_data.contains("tileImage"))
        {
            std::string btag = obj_data["tileImage"][0];

            int x = obj_data["tileImage"][1];
            int y = obj_data["tileImage"][2];
            
            CRect rt(x * TileSize, y * TileSize, (x + 1) * TileSize, (y + 1) * TileSize);

            m_pTiles[x][y].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_USERBUTTON, rt, this, IDC_RADIO_TEXTURE);

            m_pTiles[x][y].SetTileTag(CastStr(btag));
            m_pTiles[x][y].SetTilePos({x,y});

            if (obj_data.contains("tileCollider"))
            {
                POINT tmp;
                tmp.x = obj_data["tileCollider"][0];
                tmp.y = obj_data["tileCollider"][1];
                m_pTiles[x][y].SetColliderLeftTop(tmp);
            }
        }
    }

    file.close();

    CPaintDC dc(this);
    CRect rect;
    GetClientRect(&rect);
    dc.FillSolidRect(&rect, GetSysColor(COLOR_BTNFACE));
    Invalidate();
    UpdateWindow();

}

void MainWin::NewData(int _tileWidth, int _tileHeight)
{
    for (int i = 0; i < MaxTileMapHeight; i++)
        delete[] m_pTiles[i];
    delete[] m_pTiles;

    m_pTiles = new TileButton * [MaxTileMapWidth];
    for (int i = 0; i < MaxTileMapWidth; i++)
        m_pTiles[i] = new TileButton[MaxTileMapHeight];

    CRect rt = btnRt;

    for (int i = 0; i < _tileHeight; i++)
    {
        for (int j = 0; j < _tileWidth; j++)
        {
            m_pTiles[j][i].Create(_T(""), WS_CHILD | WS_VISIBLE | BS_USERBUTTON, rt, this, IDC_RADIO_TEXTURE);
            m_pTiles[j][i].SetTilePos({ j,i });
            rt.OffsetRect(TileSize, 0);
        }
        rt.OffsetRect(0, TileSize);
        rt.OffsetRect(-TileSize * _tileWidth, 0);
    }

    CPaintDC dc(this);
    CRect rect;
    GetClientRect(&rect);
    dc.FillSolidRect(&rect, GetSysColor(COLOR_BTNFACE));
    Invalidate();
    UpdateWindow();
}

std::string MainWin::CastWstr(std::wstring& _wstr)
{
    std::string str;
    str.assign(_wstr.begin(), _wstr.end());
    return str;
}

std::wstring MainWin::CastStr(std::string& _str)
{
    std::wstring wstr;
    wstr.assign(_str.begin(), _str.end());
    return wstr;
}


