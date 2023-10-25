#include "Engine.h"
#include "Simulation.h"
#include "Engine/SplashScreen.h"

Engine::Simulation::Simulation()
{
}

Engine::Simulation::~Simulation()
{
}

void Engine::Simulation::PreInitialize()
{
	Logger::PrindDebugSeparator();
	Logger::PrintLog(L"Application Starting...\n");
	Logger::PrintLog(L"Game Name: %s\n", PerGameSettings::GameName());
	Logger::PrintLog(L"Boot Time: %s\n", Time::GetDateTimeString().c_str());
	Logger::PrintLog(L"Engine Mode: %s\n", Engine::EngineModeToString().c_str());
	Logger::PrindDebugSeparator();

	SplashScreen::Open();
	//SplashScreen::AddMessages(L"Starting Application...");
}
