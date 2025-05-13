#include "../2Q_Engine/pch.h"

class D2DRenderer;
class Time;
class Input;
class World;

class Debug;
class Sound;

class CollisionManager;
class Player;
class Ground;

class GameProcess
{
private:
	HWND m_hwnd;
	MSG m_msg;
	D2DRenderer* m_D2DRenderer;
	Time* m_pTime;
	Input* m_pInput;
	World* m_pWorld;
	Debug* m_pDebug;
	Sound* m_pSound;
	CollisionManager* collisionManager;
	vector<Ground*> m_ground;
	

	WCHAR m_szTitle[100];

public:

	static const int m_screenWidth = 1920;// 1024;
	static const int m_screenHeight = 1080;// 768;
public:
	HRESULT Initialize(HINSTANCE hInstance);


	void Loop();
	void GameLoop();
	void Update(float dt);
	void Render();

	void CalculateFps(float dt);

	void Finalize();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};