#pragma once
#include <afxwin.h>
class ImageButton : public CButton
{
	DECLARE_DYNAMIC(ImageButton)
public:
	afx_msg void OnPaint();
	afx_msg void OnButtonClicked();

	void SetTileTag(std::wstring _tileTag);
private:
	CImage* m_pImage;
	std::wstring m_tileTag;

	DECLARE_MESSAGE_MAP()
};

