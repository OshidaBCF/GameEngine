#pragma once

#include "Platform/Windows/iApplication.h"

namespace Engine {
	class ENGINE_API Simulation : public Win32::IApplication {

	public:
		Simulation();
		~Simulation();

		void PreInitialize() override;
	};
}