#include "pch.h"
#include "Input.h"
Input* Input::m_pInputInstance = nullptr;

Input::Input(HWND hwnd)
    : m_hwnd(hwnd), m_realMousePos{}, m_key{}, m_keyInfo{}
{
    m_key =
    {
        VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
        'Q','W','E','R','T','Y','U','I',
        'O','P','A','S','D','F','G','Z',
        'X','C','V','B',
        VK_MENU, VK_CONTROL, VK_SPACE, VK_RETURN, VK_ESCAPE,
        VK_LSHIFT, VK_RSHIFT, VK_LBUTTON, VK_RBUTTON,
        '7','8','9','0',VK_OEM_MINUS,VK_OEM_PLUS,
    };

    for (int i = 0; i < (int)KEY::LAST; ++i)
        m_keyInfo.push_back(KeyInfo{ KEY_STATE::NONE,false });

}

Input::~Input()
{
    m_key.clear();
    m_keyInfo.clear();
}

void Input::Initialize()
{
}

void Input::Update()
{
    if (nullptr != GetFocus()) InFocus();
    else OutFocus();
    MousePos();
}

void Input::Finalize()
{
}

KEY_STATE Input::GetKeyState(KEY _Key)
{
    return m_keyInfo[(int)_Key].state;
}

POINT Input::GetMousePos()
{
    return m_worldMousePos;
}

void Input::InFocus()
{
    for (int i = 0; i < (int)KEY::LAST; ++i)
    {
        if (GetAsyncKeyState(m_key[i]) & 0x8000)
        {
            if (m_keyInfo[i].isPushed)
                m_keyInfo[i].state = KEY_STATE::HOLD;
            else
                m_keyInfo[i].state = KEY_STATE::TAP;

            m_keyInfo[i].isPushed = true;
        }
        else
        {
            if (m_keyInfo[i].isPushed)
                m_keyInfo[i].state = KEY_STATE::AWAY;
            else
                m_keyInfo[i].state = KEY_STATE::NONE;

            m_keyInfo[i].isPushed = false;
        }
    }
}

void Input::OutFocus()
{
    for (int i = 0; i < (int)KEY::LAST; ++i)
    {
        m_keyInfo[i].isPushed = false;
        if (KEY_STATE::TAP == m_keyInfo[i].state ||
            KEY_STATE::HOLD == m_keyInfo[i].state)
            m_keyInfo[i].state = KEY_STATE::AWAY;
        else if (KEY_STATE::AWAY == m_keyInfo[i].state)
            m_keyInfo[i].state = KEY_STATE::NONE;
    }
}

void Input::MousePos()
{
    POINT tmp;
    GetCursorPos(&tmp);
    ScreenToClient(m_hWnd, &tmp);
    m_realMousePos.x = (float)tmp.x;
    m_realMousePos.y = (float)tmp.y;
    m_worldMousePos.x = (float)tmp.x +m_cameraVector.x;
    m_worldMousePos.y = (float)tmp.y +m_cameraVector.y;
}
