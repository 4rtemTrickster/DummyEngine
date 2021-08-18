#pragma once
#include "Application/Application.h"

#ifdef DE_PLATFORM_WINDOWS

extern Dummy::Application* Dummy::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Dummy::CreateApplication();
    app->Run();
    delete app;
    
}
#endif