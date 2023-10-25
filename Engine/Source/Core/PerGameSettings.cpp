#include "Engine.h"

PerGameSettings* PerGameSettings::inst;

PerGameSettings::PerGameSettings()
{
	inst = this;
	wcscpy_s(inst->m_GameName, L"undefined");
	wcscpy_s(inst->m_ShortName, L"undefined");
	wcscpy_s(inst->m_BootTime, Time::GetDateTimeString(true).c_str());
	wcscpy_s(inst->m_SplashURL, L"..\\Engine\\Content\\Images\\OlympusSplash.bmp");
}

PerGameSettings::~PerGameSettings()
{
}