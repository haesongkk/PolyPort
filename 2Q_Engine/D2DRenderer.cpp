#include "pch.h"

#include "D2DRenderer.h"

#include "AnimationAsset.h"
#include "GameProcess.h"

#include <istream>
#include <fstream>
#include <filesystem>

namespace FS = std::filesystem;

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")	// writefactory

IDWriteFactory* D2DRenderer::m_pDWriteFactory = nullptr;
ID2D1HwndRenderTarget* D2DRenderer::m_pRenderTarget = nullptr;
D2DRenderer* D2DRenderer::m_instance = nullptr;

D2DRenderer::D2DRenderer()
	: m_pD2DFactory(nullptr)
	, m_pDWriteTextFormat(nullptr)
	, m_pWICFactory(nullptr)
	, m_pBrush(nullptr)
	, m_hwnd(NULL)
{
}

D2DRenderer::~D2DRenderer()
{
	if (m_pD2DFactory != nullptr)
	{
		m_pD2DFactory->Release();
		m_pD2DFactory = nullptr;
	}
		
	if (m_pDWriteFactory != nullptr)
	{
		m_pDWriteFactory->Release();
		m_pDWriteFactory = nullptr;
	}
	
	if (m_pDWriteTextFormat != nullptr)
	{
		m_pDWriteTextFormat->Release();
		m_pDWriteTextFormat = nullptr;
	}

	if (m_pWICFactory != nullptr)
	{
		m_pWICFactory->Release();
		m_pWICFactory = nullptr;
	}

	if (m_pBrush != nullptr)
	{
		m_pBrush->Release();
		m_pBrush = nullptr;
	}
}

HRESULT D2DRenderer::Initialize(HWND hwnd)
{
	HRESULT hr = S_OK;
	// COM 사용 시작
	hr = CoInitialize(NULL);
	m_hwnd = hwnd;
	if (SUCCEEDED(hr))
	{
		/*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
			이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
			DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
		*/
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	}
	if (SUCCEEDED(hr))
	{
		/*
		Direct3D 장치에 바인딩된 리소스를 만듭니다.
		Direct3D 장치가 손실된 경우(예: 디스플레이 변경, 원격, 비디오 카드 제거 등)
		리소스를 다시 생성해야 하는 경우를 대비하여 모두 여기에 중앙 집중화되어 있습니다.
		*/

		RECT rc;
		::GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U ScreenSize = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);


		// Create a Direct2D render target.
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, ScreenSize),
			&m_pRenderTarget);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pBrush);
	}

	if (SUCCEEDED(hr))
	{
		// Create WIC factory
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_pWICFactory)
		);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pBrush);
	}
	if (SUCCEEDED(hr))
	{
		// DirectWrite 팩터리를 만듭니다.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}
	if (SUCCEEDED(hr))
	{
		// DirectWrite 텍스트 형식 개체를 만듭니다.
		hr = m_pDWriteFactory->CreateTextFormat(
			L"", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15.0f,   // Font Size
			L"", //locale
			&m_pDWriteTextFormat
		);
	}

	// 브러쉬, DXGI 팩토리는 필요 없을 것 같아 생성하지 않았음. 추후 필요해지면 생성할 예정

	return hr;
}

ID2D1Bitmap* D2DRenderer::CreateBitmapFromFile(wstring strFilePath)
{
	ID2D1Bitmap* ppID2D1Bitmap = nullptr;
	// 문자열과 포인터 쌍에서 문자열만 같으면 해당 원소를 찾는다.
	auto it = m_sharingBitmaps.find(strFilePath);
	if (it != m_sharingBitmaps.end())
	{
		ID2D1Bitmap* pBitmap = it->second;
		ppID2D1Bitmap = pBitmap;
		if(pBitmap !=nullptr) pBitmap->AddRef();
		
		return ppID2D1Bitmap;
	}

	// 컨테이너에 이미 같은 경로가 있으면 다시 만들지 않는다. 
	// 즉 기존 비트맵의 레퍼런스 증가시키고 포인터 변수에 값을 넣는다.
	HRESULT hr;
	

	// Create a decoder
	IWICBitmapDecoder* pDecoder = NULL;
	IWICFormatConverter* pConverter = NULL;

	hr = m_pWICFactory->CreateDecoderFromFilename(
		strFilePath.c_str(),                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr = m_pWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &ppID2D1Bitmap);
	}

	// 파일을 사용할때마다 다시 만든다.
	if (pConverter)
		pConverter->Release();

	if (pDecoder)
		pDecoder->Release();

	if (pFrame)
		pFrame->Release();

	

	m_sharingBitmaps.insert(make_pair(strFilePath, ppID2D1Bitmap));
	return ppID2D1Bitmap;
}

AnimationAsset* D2DRenderer::CreateAnimationAsset(wstring strFilePath)
{
	AnimationAsset* pAsset;
	auto it = m_sharingAnimationAssets.find(strFilePath);
	if (it != m_sharingAnimationAssets.end())
	{
		pAsset = it->second;
		pAsset->AddRef();
		return pAsset;
	}

	pAsset = new AnimationAsset;
	pAsset->SetBitmap(CreateBitmapFromFile(strFilePath));
	m_sharingAnimationAssets.insert(make_pair(strFilePath, pAsset));
	pAsset->AddRef();
	return pAsset;
}

void D2DRenderer::DrawRectangle(ID2D1RenderTarget* pRenderTarget, const D2D1_RECT_F rect, const D2D1_COLOR_F color)
{
	//m_pBrush->SetColor(color);
	//pRenderTarget->DrawRectangle(rect, m_pBrush);
}

// 텍스트 파일로 애니메이션 어셋 추가 (키는 그대로 이미지 파일 경로임)
// testLoadMotion.txt 형식대로 저장해야 사용 가능
AnimationAsset* D2DRenderer::CreateAnimationAssetFromFile(const wstring strFilePath)
{
	std::ifstream file(strFilePath);
	assert(file.is_open());

	AnimationAsset* pAsset = nullptr;
	AnimationInfo pInfo{ "" };

	string line;

	bool isFirtLine = true;
	bool isNameLine = false;

	// 한줄씩 파일 읽기
	while (getline(file, line))
	{
		// 첫줄에 적힌 이미지 파일 경로로 어셋 추가
		if (isFirtLine)
		{
			map<wstring, AnimationAsset*> tmp = m_sharingAnimationAssets;
			isFirtLine = false;
			wstring wstr;
			wstr.assign(line.begin(), line.end());
			pAsset = CreateAnimationAsset(wstr);
			for (auto it = tmp.begin(); it != tmp.end(); it++)
				if ((*it).second == pAsset)
					return pAsset;
			continue;
		}

		if (line.empty())
		{
			isNameLine = true;
			if(pInfo.m_name != "")
				pAsset->m_animations.push_back(pInfo);
			pInfo = AnimationInfo{};
			continue;
		}

		const string delimiter = ",";
		size_t pos = 0, index = 0;

		// 애니메이션 인포의 이름과 속도
		if (isNameLine)
		{
			if (line.empty()) break;

			isNameLine = false;

			while (pos != std::string::npos)
			{
				pos = line.find(delimiter);
				string token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());

				switch (index)
				{
					case 0:
						pInfo.m_name = token;
						break;
					case 1:
						pInfo.progressTime = stof(token);
						break;
				}
				index++;
			}

			continue;
		}


		float top, left, bottom, right;

		// 그 외의 경우 frame info 추가
		while (pos != std::string::npos)
		{
			pos = line.find(delimiter);
			string token = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());

			switch (index)
			{
				case 0:
					top = stof(token);
					break;
				case 1:
					left = stof(token);
					break;
				case 2:
					bottom = stof(token);
					break;
				case 3:
					right = stof(token);
					break;
			}
			index++;
		}
		// 한 줄 씩 프레임 인포 추가
		pInfo.m_frames.push_back(FrameInfo(top, left, bottom, right));
	}

	if(pAsset!=nullptr && pInfo.m_name != "") pAsset->m_animations.push_back(pInfo);

	file.close();
	return pAsset;

}

void D2DRenderer::ReleaseBitmap(wstring strFilePath)
{
	auto it = m_sharingBitmaps.find(strFilePath);

	int count = it->second->Release();

	if (count > 0)
		return;

	if (it != m_sharingBitmaps.end())
		m_sharingBitmaps.erase(it);
}

void D2DRenderer::ReleaseBitmap(ID2D1Bitmap* pBitmap)
{
	auto it = std::find_if(m_sharingBitmaps.begin(), m_sharingBitmaps.end(), [&](const auto& pair) {
		return pair.second == pBitmap;
		});

	int count = it->second->Release();

	if (count > 0)
		return;

	if (it != m_sharingBitmaps.end())
		m_sharingBitmaps.erase(it);
}



void D2DRenderer::ReleaseAnimationAsset(wstring strFilePath) // 애니메이션 Release해줄 때 Bitmap도 같이 Release 해줘야 하는가?
{
	auto it = m_sharingAnimationAssets.find(strFilePath);

	int count = it->second->Release();

	if (count > 0)
		return;
	if (it != m_sharingAnimationAssets.end())
		m_sharingAnimationAssets.erase(it);
}

void D2DRenderer::ReleaseAnimationAsset(AnimationAsset* pAsset)
{
	auto it = std::find_if(m_sharingAnimationAssets.begin(), m_sharingAnimationAssets.end(), [&](const auto& pair) {
		return pair.second == pAsset;
		});

	int count = it->second->Release();

	if (count > 0)
		return;

	if(it !=m_sharingAnimationAssets.end())
		m_sharingAnimationAssets.erase(it);
}

void D2DRenderer::EndDraw() // 그래픽카드에 문제가 있을 경우 EndDraw가 오류 나는 경우가 있기 때문에 예외 처리해줌
{
	HRESULT hr = m_pRenderTarget->EndDraw();
	assert(hr == S_OK, "EndDraw Error");
}

// 폴더 경로를 받아서 한번에 비트맵, 애니메이션 어셋 생성하는 함수
void D2DRenderer::LoadResource(wstring _folderPath)
{
	FS::path folderPath(_folderPath);

	assert(FS::exists(folderPath) && FS::is_directory(folderPath));

	for (const auto& entry : FS::directory_iterator(folderPath))
	{
		const FS::path& filePath = entry.path();

		if (!FS::is_regular_file(filePath) || !filePath.has_extension()) continue;

		// 파일 확장자를 받아서 소문자로 변환한다
		std::wstring fileExtension = filePath.extension().c_str();
		std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);

		std::wstring wFilePath = filePath.wstring();

		// 이미지 파일이면 비트맵 추가
		if (fileExtension == L".jpg" || fileExtension == L".jpeg" || fileExtension == L".png"
			|| fileExtension == L".bmp" || fileExtension == L".webp")
		{
			CreateBitmapFromFile(wFilePath);
		}
		// 텍스트 파일이면 어셋 추가
		else if (fileExtension == L"txt")
		{
			//CreateAnimationAssetFromFile(wFilePath); 
		}
	}
}



