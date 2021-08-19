#pragma once
#include "Application/Application.h"
#include "Log/Log.h"

#ifdef DE_PLATFORM_WINDOWS

extern Dummy::Application* Dummy::CreateApplication();

int main(int argc, char** argv)
{
    
    Dummy::Log::Init();

    Dummy::Log::GetCoreLogger()->trace("Core logger initialized!");
    
    auto app = Dummy::CreateApplication();
    app->Run();
    delete app;
    
}
#endif