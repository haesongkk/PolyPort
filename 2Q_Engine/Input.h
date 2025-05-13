#pragma once
enum class KEY_STATE { NONE, TAP, HOLD, AWAY, };

enum class KEY
{
    LEFT, RIGHT, UP, DOWN,
    Q, W, E, R, T, Y, U, I,
    O, P, A, S, D, F, G, Z,
    X, C, V, B,
    ALT, CTRL, SPACE, ENTER, ESC,
    LSHIFT, RSHIFT, LBUTTON, RBUTTON,
    SEVEN,EIGHT,NINE,ZERO,MINUS,PLUS,
    LAST,
};

class GameProcess;
class Input
{
public:
    struct KeyInfo
    {
        KEY_STATE state;
        bool isPushed;
    };
    static Input* m_pInputInstance;
    Input(HWND hwnd);
    virtual ~Input();

    virtual void Initialize();
    virtual void Update();
    virtual void Finalize();

    KEY_STATE GetKeyState(KEY _Key);

    POINT GetRealMousePos() { return m_realMousePos; }
    POINT GetWorldMousePos() { return m_worldMousePos; }

    POINT GetMousePos();
    void SetCameraVector(Vector2D cameraVector) { m_cameraVector = cameraVector; }

    static Input* GetInstance()
    {
        return m_pInputInstance;
    }
private:
    void InFocus();
    void OutFocus();
    void MousePos();

    HWND m_hWnd;
    std::vector<int> m_key;
    std::vector<KeyInfo> m_keyInfo;
    HWND m_hwnd;
    POINT m_realMousePos;
    POINT m_worldMousePos;
    Vector2D m_cameraVector;
};

