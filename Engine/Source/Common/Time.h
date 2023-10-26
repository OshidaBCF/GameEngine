#pragma once
#include <string>

namespace Time {
	// Get current time
	WSTRING ENGINE_API GetTime(bool stripped = false);

	// Get current date
	WSTRING ENGINE_API GetDate(bool stripped = false);

	// Get current date and time
	WSTRING ENGINE_API GetDateTimeString(bool stripped = false);
}