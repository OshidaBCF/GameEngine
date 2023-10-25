#include "BlankProject.h"
#include "Engine/Simulation.h"
#include "Platform/Windows/WinEntry.h"

class BlankProject : public Engine::Simulation {
	// Application

public:
	// Constructor
	BlankProject();

	// Destructor
	~BlankProject();


public:
	// Called to setup our pergame settings
	void SetupPerGameSettings();

	// Called to Initialize the Application
	void Initialize();

	// Game Loop - Called on a loop while the Application is running
	void Update();
};


ENTRYAPP(BlankProject)

BlankProject::BlankProject()
{
}

BlankProject::~BlankProject()
{
}

void BlankProject::SetupPerGameSettings()
{
	// Set pergame settings
	PerGameSettings::SetGameName(IDS_PERGAMENAME);
	PerGameSettings::SetShortName(IDS_SHORTNAME);
	PerGameSettings::SetMainIcon(IDI_MAINICON);
	PerGameSettings::SetSplashURL(IDS_SPLASHURL);
}

void BlankProject::Initialize()
{
}

void BlankProject::Update()
{
	//Logger::PrintLog(L"Loop\n");
}
