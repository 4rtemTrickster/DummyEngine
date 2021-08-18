#include "Application.h"

#include <iostream>


namespace Dummy
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(true)
        {
            std::cout << "IT WORK'S" << std::endl;
        }
    }
} 