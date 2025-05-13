// Demo.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "../2Q_Engine/pch.h"
#include "../2Q_Engine/GameProcess.h"
#include "../2Q_Engine/D2DRenderer.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	// 게임 진행 클래스
	// 내부에서 윈도 생성과 메시지 콜백을 처리한다.
	// 또한 그래픽스 엔진 등을 포함한다.
	GameProcess* pGameProcess = new GameProcess();
	pGameProcess->Initialize(hInstance);
	pGameProcess->Loop();
	pGameProcess->Finalize();

	delete pGameProcess;
	//_CrtDumpMemoryLeaks();
	
	return 0; // (int)msg.wParam;
}
