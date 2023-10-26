#include "Engine.h"
#include "Simulation.h"
#include "Engine/SplashScreen.h"

namespace Engine
{
	Simulation::Simulation()
		: Win32::Window(L"MainApplication", NULL)
	{

	}

	Simulation::~Simulation()
	{
	}

	void Simulation::PreInitialize()
	{
		Logger::PrindDebugSeparator();
		Logger::PrintLog(L"Application Starting...\n");
		Logger::PrintLog(L"Game Name: %s\n", PerGameSettings::GameName());
		Logger::PrintLog(L"Boot Time: %s\n", Time::GetDateTimeString().c_str());
		Logger::PrintLog(L"Engine Mode: %s\n", Engine::EngineModeToString().c_str());
		Logger::PrindDebugSeparator();

		SplashScreen::Open();

		Win32::Window::RegisterNewClass();
		Win32::Window::Initialize();
	}

	LRESULT Simulation::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{

		}
		return Window::MessageHandler(hwnd, message, wParam, lParam);
	}

}