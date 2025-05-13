#pragma once
#include <list>
#include <map>
class AnimationAsset;
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	static ID2D1HwndRenderTarget* m_pRenderTarget;
	static D2DRenderer* m_instance;
	static IDWriteFactory* m_pDWriteFactory;
private:
	HWND m_hwnd;
	ID2D1Factory* m_pD2DFactory; //D2D 개체 인터페이스 포인터 변수
	IWICImagingFactory* m_pWICFactory; // 비트맵 생성 하는데 필요한 팩토리
	IDWriteTextFormat* m_pDWriteTextFormat; // 기본 텍스트 출력을 위한 Format

	ID2D1SolidColorBrush* m_pBrush;	// 렌더타겟이 생성하는 리소스 역시 장치의존

	map<wstring, AnimationAsset*> m_sharingAnimationAssets;
	map<wstring, ID2D1Bitmap*> m_sharingBitmaps;
public:
	HRESULT Initialize(HWND hwnd);

	ID2D1Bitmap* CreateBitmapFromFile(wstring strFilePath);
	AnimationAsset* CreateAnimationAsset(wstring strFilePath);
	IDWriteTextFormat* CreateTextFormat(const wstring& font, int size);

	void DrawRectangle(ID2D1RenderTarget* pRenderTarget, D2D1_RECT_F rect, D2D1_COLOR_F color);
	AnimationAsset* CreateAnimationAssetFromFile(wstring strFilePath);

	void ReleaseBitmap(wstring strFilePath);
	void ReleaseBitmap(ID2D1Bitmap* pBitmap);

	void ReleaseAnimationAsset(wstring strFilePath);
	void ReleaseAnimationAsset(AnimationAsset* pAsset);

	void EndDraw();

	

	ID2D1SolidColorBrush* GetBrush() const { return m_pBrush; }

	void LoadResource(wstring _folderPath);

};

