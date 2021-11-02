#pragma once
#include "../Core.h"
#include "../Log/Log.h"
#include "../Window/Window.h"

namespace Dummy
{
    class DUMMY_API Application
    {
    public:

        Application();
        virtual ~Application();
        
        void Run();

    protected:
        std::unique_ptr<Window> window;
        bool bRunning = true;
    };

    
    /**
     * \brief To be defined in CLIENT
     * \return Returns an application instance
     */
    Application* CreateApplication();
}
