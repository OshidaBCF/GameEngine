#pragma once

#include <Uxtheme.h>
#pragma comment(lib, "uxtheme.lib")

namespace Win32
{
	class ENGINE_API Window : public Win32::SubObject, public Win32::Caption
	{
	public:
		Window(WSTRING title, HICON icon, WindowType type = RESIZABLE);
		~Window();

		virtual void Initialize() override;

		virtual LRESULT MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

		void OnNonClientPaint(HRGN region);

		void OnNonClientCreate();

		void RedrawWindow();

		void onNonClientActivate(bool active);

		void PaintCaption(HDC hdc);

		void OnNonClientLeftMouseButtonDown();

		void OnGetMinMaxInfo(MINMAXINFO* minmax);

		void OnExitSizeMove();

		void OnPaint();

	protected:
		SIZE m_Size;
		WindowType m_Type;
		bool m_Active;

	public:
		SIZE Size() { return m_Size; }
		void Size(SIZE size) { m_Size = size; }
		void Size(int x, int y) { m_Size.cx = x; m_Size.cy = y;}
		bool Active() { return m_Active; }
		void Active(bool active) { m_Active = active; }
	};
}