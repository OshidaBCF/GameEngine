#pragma once

#include "Core/CoreDefinitions.h"

#include "Engine/GEngine.h"

#include "Common/Logger.h"
#include "Common/Time.h"
#include "Core/PerGameSettings.h"

#ifdef WIN32
	#include "Platform/Windows/Win32Utils.h"
	#include "Platform/Windows/SubObject.h"
	#include "Platform/Windows/w32Caption.h"
	#include "Platform/Windows/Window.h"
	#include "Platform/Windows/iApplication.h"
#endif