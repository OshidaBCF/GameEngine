#include "Engine.h"

namespace Engine
{
	GEngine g_GameEngine;
	void SetMode(EngineMode mode)
	{
		g_GameEngine.SetEngineMode(mode);
	}

	EngineMode GetMode()
	{
		return g_GameEngine.GetEngineMode();
	}

	WSTRING ENGINE_API EngineModeToString()
	{
		switch (Engine::GetMode())
		{
		case EngineMode::DEBUG:     return L"Debug";
		case EngineMode::RELEASE:   return L"Release";
		case EngineMode::EDITOR:    return L"Editor";
		case EngineMode::SERVER:    return L"Server";
		default:                    return L"None";
		}
	}
}

GEngine::GEngine()
{
#ifdef _DEBUG
	m_EngineMode = EngineMode::DEBUG;
#else
	m_EngineMode = EngineMode::RELEASE;
#endif
}

GEngine::~GEngine()
{
}

EngineMode GEngine::GetEngineMode()
{
	return m_EngineMode;
}

void GEngine::SetEngineMode(EngineMode mode)
{
	m_EngineMode = mode;
}