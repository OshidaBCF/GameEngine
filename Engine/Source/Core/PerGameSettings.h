#pragma once

class ENGINE_API PerGameSettings {

	// Getter and Setter for singleton static class
private:
	static PerGameSettings* inst;

public:
	static PerGameSettings* Instance() { return inst; }

	//Constructor
	PerGameSettings();
	~PerGameSettings();

private:
	// Per Game Private Variable
	WCHAR m_GameName[MAX_NAME_STRING];
	WCHAR m_ShortName[MAX_NAME_STRING];
	HICON m_MainIcon;
	WCHAR m_BootTime[MAX_NAME_STRING];
	WCHAR m_SplashURL[MAX_NAME_STRING];

public:
	static WCHAR* GameName() { return inst->m_GameName; }
	static void SetGameName(UINT id) { LoadString(HInstance(), id, inst->m_GameName, MAX_NAME_STRING); }

	static WCHAR* ShortName() { return inst->m_ShortName; }
	static void SetShortName(UINT id) { LoadString(HInstance(), id, inst->m_ShortName, MAX_NAME_STRING); }

	static HICON MainIcon() { return inst->m_MainIcon; }
	static void SetMainIcon(UINT id) { LoadIcon(HInstance(), MAKEINTRESOURCE(id)); }

	static WCHAR* BootTime() { return inst->m_BootTime; }

	static WCHAR* SplashURL() { return inst->m_SplashURL; }
	static void SetSplashURL(UINT id) { LoadString(HInstance(), id, inst->m_SplashURL, MAX_NAME_STRING); }

};