#include "Engine.h"
#include "SplashScreen.h"

#include "Platform/Windows/Win32Utils.h"

namespace SplashScreen
{
	#define MW_OUTPUTMESSAGE (WM_USER + 0x0001)

	SplashWindow* m_SplashWindow;

	void Open()
	{
		if (m_SplashWindow != nullptr)
			return;
		m_SplashWindow = new SplashWindow();
	}

	void Close()
	{
		/*if (m_SplashWindow == nullptr)
			return;
		m_SplashWindow = nullptr;*/
	}

	void AddMessages(const WCHAR* message)
	{
		PostMessage(m_SplashWindow->Handle(), MW_OUTPUTMESSAGE, (WPARAM)message, 0);
	}
}

SplashWindow::SplashWindow()
	: Win32::Window(L"SplashScreen", NULL, Win32::WindowType::POPUP)
{
	wcscpy_s(m_outputMessage, L"SplashScreen Starting...");
	Win32::Window::RegisterNewClass();
	Size(500, 600);
	Win32::Window::Initialize();
}

SplashWindow::~SplashWindow()
{
}

LRESULT SplashWindow::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		HBITMAP hbitmap;
		HDC hdc, hmemdc;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hwnd, &ps);

		Win32::Utils::AddBitmap(PerGameSettings::SplashURL(), hdc);

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));

		if (Engine::GetMode() != Engine::EngineMode::RELEASE)
		{
			WSTRING engineModeText = Engine::EngineModeToString() + L" Mode";
			SetTextAlign(hdc, TA_RIGHT);
			TextOut(hdc, m_Size.cx - 15, 15, engineModeText.c_str(), wcslen(engineModeText.c_str()));
		}

		SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, m_Size.cx / 2, m_Size.cy - 30, m_outputMessage, wcslen(m_outputMessage));
		EndPaint(hwnd, &ps);
	}
	break;
	case MW_OUTPUTMESSAGE:
	{
		WCHAR* msg = (WCHAR*)wParam;
		wcscpy_s(m_outputMessage, msg);
		RedrawWindow();
		return 0;
	}
	}
	return Window::MessageHandler(hwnd, message, wParam, lParam);
}
