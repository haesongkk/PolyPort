#pragma once
#include <queue>

struct DebugBox
{
	D2D1_MATRIX_3X2_F matrix;
	Vector2D size;
	bool bRed;
	wstring text;
};

class Debug
{
public:
	Debug();
	~Debug();

	void Update();

	static bool ModeSwitch();
	static void Log(wstring _text);
	static void Text(wstring _text);
	static void Rect(D2D1_MATRIX_3X2_F _matrix, Vector2D _size, bool _bRed, wstring _text = L"");

private:
	ID2D1SolidColorBrush* m_pBlackBrush;
	ID2D1SolidColorBrush* m_pRedBursh;
	IDWriteTextFormat* m_pWriteTextFormat;

	static bool m_bDebug;
	static vector<wstring> m_texts;
	static vector<DebugBox> m_boxes;
	static queue<wstring> m_logs;
};
