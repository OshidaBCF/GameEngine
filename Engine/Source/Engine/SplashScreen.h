#pragma once

#include "Platform/Windows/Window.h"

namespace SplashScreen
{
	void ENGINE_API Open();
	void ENGINE_API Close();
	void ENGINE_API AddMessages(const WCHAR* message);
}

class ENGINE_API SplashWindow : public Win32::Window
{
public:
	SplashWindow();
	~SplashWindow();

	virtual LRESULT MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	WCHAR m_outputMessage[MAX_NAME_STRING];
};