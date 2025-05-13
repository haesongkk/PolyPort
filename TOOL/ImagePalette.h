#pragma once
#include <vector>
class ImageButton;
class ImagePalette : public CDialog
{
    DECLARE_DYNAMIC(ImagePalette)

public:
    ImagePalette();
    virtual ~ImagePalette();

public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:
    ImageButton* m_pButtons;
    std::vector<ImageButton*> m_pImageButtons;
    DECLARE_MESSAGE_MAP()
};

