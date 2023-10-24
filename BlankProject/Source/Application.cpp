#include "pch.h"
#include "Application.h"
#include "Platform/Windows/WinEntry.h"

ENTRYAPP(Application)

Application::Application()
{
}

Application::~Application()
{
}

void Application::Initialize()
{
	MessageBox(0, L" I Have loaded up ", 0, 0);
}

void Application::Update()
{
	MessageBox(0, L" Loop ", 0, 0);
}
