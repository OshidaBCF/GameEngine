﻿#include "Engine.h"
#include "Window.h"

#define DCX_USESTYLE 0x00010000

namespace Win32
{
	Window::Window(WSTRING title, HICON icon, WindowType type)
		: Win32::SubObject(title, title, icon), m_Type(type)
	{

		Size(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	}

	Window::~Window()
	{
	}

	void Window::Initialize()
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);

		RECT R = { 0, 0, m_Size.cx, m_Size.cy };
		AdjustWindowRect(&R, m_Type, false);
		int width = R.right - R.left;
		int height = R.bottom - R.top;

		m_Handle = CreateWindow(m_Class.c_str(), m_Title.c_str(), 
			m_Type, ((desktop.right/2) - (m_Size.cx / 2)), ((desktop.bottom / 2) - (m_Size.cy / 2)), m_Size.cx, m_Size.cy, 0, 0, HInstance(), (void*)this);

		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);
	}

	LRESULT Window::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_NCCREATE:		 { OnNonClientCreate(); }									return true;
		case WM_NCACTIVATE:		 { onNonClientActivate(LOWORD(wParam) != WA_INACTIVE); }	return true;
		case WM_NCPAINT:		 { OnNonClientPaint((HRGN)wParam); }						return false;
		case WM_NCLBUTTONDOWN:	 { OnNonClientLeftMouseButtonDown(); }						break;
		case WM_NCLBUTTONDBLCLK: { Win32::Utils::MaximizeWindow(Handle()); }				return 0;

		case WM_GETMINMAXINFO:	 {OnGetMinMaxInfo(((MINMAXINFO*)lParam)); }					return 0;
		case WM_EXITSIZEMOVE:	 {	OnExitSizeMove(); }		     							break;
		case WM_TIMER:			 { RedrawWindow(); }										break;
		case WM_PAINT:           { OnPaint(); }												break;
		}
		return SubObject::MessageHandler(hwnd, message, wParam, lParam);
	}

	void Window::OnNonClientPaint(HRGN region)
	{
		HDC hdc = GetDCEx(Handle(), region, DCX_WINDOW | DCX_INTERSECTRGN | DCX_USESTYLE);

		RECT rect;
		GetWindowRect(Handle(), &rect);

		SIZE size = SIZE{ rect.right - rect.left, rect.bottom - rect.top };

		HBITMAP hbmMem = CreateCompatibleBitmap(hdc, size.cx, size.cy);
		HANDLE hOld = SelectObject(hdc, hbmMem);

		HBRUSH brush = CreateSolidBrush(RGB(46, 46, 46));

		RECT newRect = RECT{ 0, 0, size.cx, size.cy };

		FillRect(hdc, &newRect, brush);

		if (Active() && !Win32::Utils::IsWindowFullscreen(Handle()))
		{
			brush = CreateSolidBrush(RGB(0, 100, 150));
			FrameRect(hdc, &newRect, brush);
		}

		PaintCaption(hdc);

		DeleteObject(brush);

		BitBlt(hdc, 0, 0, size.cx, size.cy, hdc, 0, 0, SRCCOPY);

		SelectObject(hdc, hOld);
		DeleteObject(hbmMem);

		ReleaseDC(Handle(), hdc);
	}

	void Window::OnNonClientCreate()
	{
		SetTimer(Handle(), 1, 100, NULL);
		SetWindowTheme(Handle(), L"", L"");

		Win32::Utils::ModifyClassStyle(Handle(), 0, CS_DROPSHADOW);
		Win32::Caption::AddCaptionButton(new CaptionButton(L"X", CB_CLOSE));
		Win32::Caption::AddCaptionButton(new CaptionButton(L"🗖", CB_MAXIMIZE));
		Win32::Caption::AddCaptionButton(new CaptionButton(L"🗕", CB_MINIMIZE));
	}

	void Window::RedrawWindow()
	{
		SetWindowPos(Handle(), 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_FRAMECHANGED);
		SendMessage(Handle(), WM_PAINT, 0, 0);
	}

	void Window::onNonClientActivate(bool active)
	{
		Active(active);
	}
	
	void Window::PaintCaption(HDC hdc)
	{
		RECT rect;
		GetWindowRect(Handle(), &rect);

		SIZE size = SIZE{ rect.right - rect.left, rect.bottom - rect.top };
		if (ShowTitle())
		{
			rect = RECT{ 0, 0, size.cx, 30 };

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, Active() ? RGB(255, 255, 255) : RGB(92, 92, 92));
			DrawText(hdc, m_Title.c_str(), wcslen(m_Title.c_str()), &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}

		int offset = 0;

		POINT pt;
		GetCursorPos(&pt);

		rect;
		GetWindowRect(Handle(), &rect);
		pt.x -= rect.left;
		pt.y -= rect.top;

		for (auto &button : Caption::CaptionButtons())
		{
			offset += button->Width;

			button->Rect = RECT{ size.cx - offset, 0, size.cx - offset + button->Width, 30 };

			if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y)
			{
				HBRUSH brush = CreateSolidBrush(RGB(92, 92, 92));
				FillRect(hdc, &button->Rect, brush);
				DeleteObject(brush);
			}

			if (button->Text.compare(L"🗖") == 0 && Win32::Utils::IsWindowFullscreen(Handle()))
			{
				button->Text = L"🗗";
			}
			else if (button->Text.compare(L"🗗") == 0 && !Win32::Utils::IsWindowFullscreen(Handle()))
			{
				button->Text = L"🗖";
			}

			DrawText(hdc, button->Text.c_str(), wcslen(button->Text.c_str()), &button->Rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}
	}

	void Window::OnNonClientLeftMouseButtonDown()
	{
		POINT pt;
		GetCursorPos(&pt);

		RECT rect;
		GetWindowRect(Handle(), &rect);
		pt.x -= rect.left;
		pt.y -= rect.top;

		for (auto& button : Caption::CaptionButtons())
		{
			if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y)
			{
				switch (button->Command)
				{
				case CB_CLOSE: {SendMessage(Handle(), WM_CLOSE, 0, 0); } break;
				case CB_MINIMIZE: {ShowWindow(Handle(), SW_MINIMIZE); } break;
				case CB_MAXIMIZE: {Win32::Utils::MaximizeWindow(Handle()); } break;
				}
			}
		}
	}

	void Window::OnGetMinMaxInfo(MINMAXINFO* minmax) {
		RECT WorkArea; SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
		minmax->ptMaxSize.x = (WorkArea.right - WorkArea.left);
		minmax->ptMaxSize.y = (WorkArea.bottom - WorkArea.top);
		minmax->ptMaxPosition.x = WorkArea.left;
		minmax->ptMaxPosition.y = WorkArea.top;
		minmax->ptMinTrackSize.x = 400;
		minmax->ptMinTrackSize.y = 300;
	}

	void Window::OnExitSizeMove() {
		RECT rect;
		GetWindowRect(Handle(), &rect);
		RECT WorkArea; SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
		if (rect.top < WorkArea.top + 10 && !Win32::Utils::IsWindowFullscreen(Handle()))
			Win32::Utils::MaximizeWindow(Handle());
	}

	void Window::OnPaint() {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Handle(), &ps);

		RECT rc;
		GetClientRect(Handle(), &rc);

		HBRUSH brush = CreateSolidBrush(RGB(36, 36, 36));

		FillRect(hdc, &rc, brush);

		DeleteObject(brush);

		EndPaint(Handle(), &ps);

	}
}