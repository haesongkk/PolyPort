#include "pch.h"
#include "D2DRenderer.h"
#include "GameProcess.h"
#include "Time.h"
#include "Input.h"
#include "World.h"
#include "CollisionManager.h"
#include "Sound.h"
#include "Debug.h"


HRESULT GameProcess::Initialize(HINSTANCE hInstance)
{
#pragma region _WINDOWINIT_
	/// Win32 관련
	// 윈도 클래스
	WCHAR szAppName[] = L"Direct2D Demo";
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = GameProcess::WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	// 윈도 클래스 등록
	RegisterClass(&wndclass);

	// 윈도 생성
	m_hwnd = CreateWindow(
		szAppName,
		szAppName,
		WS_POPUP,
		0, 0, m_screenWidth, m_screenHeight,
		NULL, NULL, hInstance, NULL);

	if (!m_hwnd) return S_FALSE;

	// 생성된 윈도를 화면에 표시
	ShowWindow(m_hwnd, SW_SHOWNORMAL);
	UpdateWindow(m_hwnd);

	m_D2DRenderer = new D2DRenderer;
	D2DRenderer::m_instance = m_D2DRenderer;
	HRESULT hr = m_D2DRenderer->Initialize(m_hwnd);

	m_pSound = new Sound();
	m_pSound->Initialize("../Resource/sound");

	m_pTime = new Time;
	m_pTime->Initialize();
	

	collisionManager = new CollisionManager();
	collisionManager->m_pInstance = collisionManager;

	m_pInput = new Input(m_hwnd);
	m_pWorld = new World();
	m_pInput->m_pInputInstance = m_pInput;

	m_pInput->Initialize();
	m_pWorld->Initialize();

	


	// 사운드 소스가 들어있는 폴더의 경로를 넣어준다

	m_pDebug = new Debug;



	/*for (int i = 0; i < 3; i++)
	{
		m_ground.push_back(m_pWorld->CreateGameObject<Ground>());
		m_ground[i]->SetCollider(Vector2D(200*i, 500-(64*i)), Vector2D(100, 50));
		CollisionManager::m_pInstance->AddCollider(m_ground[i]->GetCollider());
	}*/
	

	return S_OK;
}



void GameProcess::Loop()
{
	while (true)
	{
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_msg.message == WM_QUIT) break;

			DispatchMessage(&m_msg);
		}
		else
		{	
			m_pTime->Update();
			
			m_pTime->m_elapsedTime += m_pTime->GetDeltaTime();
			Update(m_pTime->GetDeltaTime());
			
		}
			m_pSound->Update();

	}
}

void GameProcess::GameLoop()
{

}

void GameProcess::Update(float dt)
{
	while (m_pTime->m_elapsedTime > 0.015)
	{

	m_pInput->Update();
	m_pTime->m_elapsedTime -= 0.015;
	//collisionManager->Update();
	
	m_pWorld->Update(0.015);
	m_pWorld->LateUpdate(0.015);
	CalculateFps(0.015);
	Render();
	}
}

void GameProcess::Render()
{
	m_D2DRenderer->m_pRenderTarget->BeginDraw();
	m_D2DRenderer->m_pRenderTarget->Clear();
	m_pWorld->Render(m_D2DRenderer->m_pRenderTarget);
	m_pDebug->Update();
	m_D2DRenderer->m_pRenderTarget->EndDraw();
}

void GameProcess::CalculateFps(float dt)
{
	static int frameCnt = -1;
	static float timeElapsed = 0.0f;

	frameCnt++;
	if (frameCnt == 0)
		return;

	timeElapsed += dt;

	//1초동안의 프레임 시간의 평균을 계산합니다.
	if (timeElapsed >= 1.0f)
	{
		float fps = static_cast<float>(frameCnt);  //Frame Per Second
		float spf = 1000.0f / fps;   // MilliSecond Per Frame

		std::wstring windowText;
		windowText.append(m_szTitle);
		windowText.append(L"  FPS: ");
		windowText.append(std::to_wstring(fps));
		windowText.append(L"  SPF: ");
		windowText.append(std::to_wstring(spf));
		windowText.append(L" Used VRAM: ");


		SetWindowText(m_hwnd, windowText.c_str());

		//다음 계산을위해 리셋
		frameCnt = 0;
		timeElapsed -= 1.0f;
	}
}

void GameProcess::Finalize()
{
	delete m_pDebug;
	delete m_pSound;
	delete m_pInput;
	delete m_pWorld;
	delete m_pTime;
	delete m_D2DRenderer;
	delete CollisionManager::m_pInstance;

}

LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

}