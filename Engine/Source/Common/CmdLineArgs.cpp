#include "Engine.h"
#include "CmdLineArgs.h"
#include <algorithm>

void CmdLineArgs::ReadArguments()
{
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);

    for (int i = 1; i < argc; ++i)
    {
        WSTRING key = argv[i];
        if (key[0] == '-')
        {
            key.erase(0, 1);

            std::transform(key.begin(), key.end(), key.begin(), ::tolower);
            ReadArgument(key.c_str());
        }
    }
}

void CmdLineArgs::ReadArgument(const WCHAR* argument)
{
    if (wcscmp(argument, L"mtail") == 0)
        Logger::StartMTail();
    if (wcscmp(argument, L"debug") == 0)
        Engine::SetMode(EngineMode::DEBUG);
    if (wcscmp(argument, L"editor") == 0)
        Engine::SetMode(EngineMode::EDITOR);
    if (wcscmp(argument, L"server") == 0)
        Engine::SetMode(EngineMode::SERVER);
}
