#pragma once

#include <string>

class ENGINE_API Logger {

	// Getter and Setter for singleton static class
private:
	static Logger* inst;

public:
	static Logger* Instance() { return inst; }

	// Constructor
	Logger();
	~Logger();

	// Print to Log File
	static void PrintLog(const WCHAR* fmt, ...);
	static WSTRING LogDirectory();
	static WSTRING LogFile();

	// Print a line of '-'
	static void PrindDebugSeparator();

	// Check to see if MTail is already Running
	static bool IsMTailRunning();

	// Start MTail App
	static void StartMTail();
};