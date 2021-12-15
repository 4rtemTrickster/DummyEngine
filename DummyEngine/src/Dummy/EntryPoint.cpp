#include "DEpch.h"
#include "EntryPoint.h"

int main(int argc, char** argv)
{
    Dummy::Log::Init();
    
    auto app = Dummy::CreateApplication();
    app->Run();
    delete app;

    return 0;
}