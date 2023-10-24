#pragma once

#include "Platform/Windows/IApplication.h"

class Application : public IApplication {
	// Application

public:
	// Constructor
	Application();

	// Destructor
	~Application();


public:
	// Called to Initialize the Application
	void Initialize();
	
	// Game Loop - Called on a loop while the Application is running
	void Update();
};