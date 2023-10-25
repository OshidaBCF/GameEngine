#pragma once
#include <string>

namespace Time {
	// Get current time
	std::wstring ENGINE_API GetTime(bool stripped = false);

	// Get current date
	std::wstring ENGINE_API GetDate(bool stripped = false);

	// Get current date and time
	std::wstring ENGINE_API GetDateTimeString(bool stripped = false);
}