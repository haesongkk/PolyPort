#include "pch.h"
#include "ImagePalette.h"

#include "TOOL.h"
#include "MainWin.h"
#include "ImageButton.h"


#include <cassert>

#include <istream>
#include <fstream>
#include <filesystem>

namespace FS = std::filesystem;

IMPLEMENT_DYNAMIC(ImagePalette, CDialog)

BEGIN_MESSAGE_MAP(ImagePalette, CDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()


ImagePalette::ImagePalette()
	:CDialog(IDD_ABOUTBOX)
{
}

ImagePalette::~ImagePalette()
{
	
}


int ImagePalette::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect btnRt = CRect(0, 0, 80,80);

	FS::path folderPath(L"../Resource/tile");
	assert(FS::exists(folderPath) && FS::is_directory(folderPath));
	int count = 0;

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
			ImageButton* btn = new ImageButton;
			btn->Create(_T(""), WS_CHILD | WS_VISIBLE | BS_USERBUTTON, btnRt, this, IDC_RADIO_TEXTURE);
			btn->SetTileTag(wFilePath);
			m_pImageButtons.push_back(btn);

			count++;
			if (count == 24)
			{
				btnRt.OffsetRect(-80 * 23, 80);
				count = 0;
			}
			else btnRt.OffsetRect(80, 0);

		}

	}
	return 0;
}