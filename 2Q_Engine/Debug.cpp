#include "pch.h"
#include "Debug.h"

#include "D2DRenderer.h"

#define TextSize 20

bool Debug::m_bDebug = false;
vector<wstring> Debug::m_texts = {};
vector<DebugBox> Debug::m_boxes = {};
queue<wstring> Debug::m_logs = {};

Debug::Debug()
	:m_pBlackBrush(), m_pRedBursh(), m_pWriteTextFormat()
{
	if (m_pBlackBrush == nullptr)
	{
		D2DRenderer::m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &m_pBlackBrush);
	}
	if (m_pRedBursh == nullptr)
	{
		D2DRenderer::m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &m_pRedBursh);
	}
	if (m_pWriteTextFormat == nullptr)
	{
		D2DRenderer::m_pDWriteFactory->CreateTextFormat(L"궁서", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, TextSize, L"", &m_pWriteTextFormat);
	}
}

Debug::~Debug()
{
	if (m_pWriteTextFormat != nullptr)
	{
		m_pWriteTextFormat->Release();
		m_pWriteTextFormat = nullptr;
	}
	if (m_pBlackBrush != nullptr)
	{
		m_pBlackBrush->Release();
		m_pBlackBrush = nullptr;
	}
	if (m_pRedBursh != nullptr)
	{
		m_pRedBursh->Release();
		m_pRedBursh = nullptr;
	}

	while (!m_logs.empty()) m_logs.pop();
	m_texts.clear();
	m_boxes.clear();
	m_texts.shrink_to_fit();
	m_boxes.shrink_to_fit();
}

void Debug::Update()
{
	if (!m_bDebug)
	{
		m_texts.clear();
		m_boxes.clear();
		return;
	}

	D2DRenderer::m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	// 로그 출력
	int count = 0;
	queue<wstring> tmpLogs = m_logs;
	while (!tmpLogs.empty())
	{
		m_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		D2DRenderer::m_pRenderTarget->DrawText(tmpLogs.front().c_str(), wcslen(tmpLogs.front().c_str()), m_pWriteTextFormat, D2D1::RectF(960, count, 1900, TextSize + count), m_pBlackBrush);
		tmpLogs.pop();
		count += TextSize * 1.5;
	}

	// 텍스트 출력
	count = 0;
	for (const auto& text : m_texts)
	{
		m_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		D2DRenderer::m_pRenderTarget->DrawText(text.c_str(), wcslen(text.c_str()), m_pWriteTextFormat, D2D1::RectF(0, count, 960, TextSize + count), m_pBlackBrush);
		count += TextSize * 1.5;
	}
	m_texts.clear();

	// 박스 출력
	for (const auto& box : m_boxes)
	{
		D2DRenderer::m_pRenderTarget->SetTransform(box.matrix);
		D2D1_RECT_F rect{ -box.size.x / 2,-box.size.y / 2 ,box.size.x / 2 ,box.size.y / 2 };
		if (box.bRed)
		{
			m_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			m_pWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

			D2DRenderer::m_pRenderTarget->DrawRectangle(rect, m_pRedBursh);
			D2DRenderer::m_pRenderTarget->DrawText(box.text.c_str(), wcslen(box.text.c_str()), m_pWriteTextFormat, rect, m_pRedBursh);

		}
		else
		{
			m_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			m_pWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

			D2DRenderer::m_pRenderTarget->DrawRectangle(rect, m_pBlackBrush);
			D2DRenderer::m_pRenderTarget->DrawText(box.text.c_str(), wcslen(box.text.c_str()), m_pWriteTextFormat, rect, m_pBlackBrush);

		}
	}
	m_boxes.clear();

}

bool Debug::ModeSwitch()
{
	return m_bDebug = !m_bDebug;
}

void Debug::Log(wstring _text)
{
	m_logs.push(_text);
	if (m_logs.size() > 8) m_logs.pop();
}

void Debug::Text(wstring _text)
{
	m_texts.push_back(_text);
}

void Debug::Rect(D2D1_MATRIX_3X2_F _matrix, Vector2D _size, bool _bRed, wstring _text)
{
	m_boxes.push_back(DebugBox{ _matrix,_size,_bRed, _text });
}
