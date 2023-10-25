#pragma once

class ENGINE_API GEngine;

namespace Engine
{
	enum EngineMode : int
	{
		NONE,
		DEBUG,
		RELEASE,
		EDITOR,
		SERVER
	};

	extern GEngine g_GameEngine;
	void ENGINE_API SetMode(EngineMode mode);
	EngineMode ENGINE_API GetMode();

	std::wstring ENGINE_API EngineModeToString();
}

using namespace Engine;
class ENGINE_API GEngine
{
public:
	GEngine();
	~GEngine();

private:
	EngineMode m_EngineMode;

public:
	EngineMode GetEngineMode();
	void SetEngineMode(EngineMode mode);
};
