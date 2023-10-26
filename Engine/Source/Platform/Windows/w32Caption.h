#pragma once

#define CB_CLOSE 0
#define CB_MINIMIZE 1
#define CB_MAXIMIZE 2

namespace Win32
{
	class Caption
	{
	public:
		struct CaptionButton
		{
			WSTRING Text = L"X";
			int Command = -1;
			int Width = 50;
			RECT Rect;

			CaptionButton(WSTRING text, int command, int width = 50) {
				Text = text;
				Command = command;
				Width = width;
			}
		};
	private:
		bool m_ShowTitle = true;

		std::list<CaptionButton*> m_CaptionButtons;

	public:
		bool ShowTitle() { return m_ShowTitle; }
		void ShowTitle(bool show) { m_ShowTitle = show; }

		void AddCaptionButton(CaptionButton* button);
		std::list<CaptionButton*> CaptionButtons() { return m_CaptionButtons; }
	};
}