#pragma once

#define ENTRYAPP(x) IApplication* EntryApplication() { return new x;}

class ENGINE_API IApplication {
	// Application

public:
	// Constructor
	IApplication();

	// Destructor
	virtual ~IApplication() {};


public:
	// Called to setup our pergame settings
	virtual void SetupPerGameSettings() = 0;

	// Called to Initialize the Application
	virtual void Initialize() = 0;

	// Game Loop - Called on a loop while the Application is running
	virtual void Update() = 0;
};

IApplication* EntryApplication();