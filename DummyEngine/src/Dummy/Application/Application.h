#pragma once
#include "../Core.h"

namespace Dummy
{
    class DUMMY_API Application
    {
    public:

        Application();
        virtual ~Application();
        
        void Run();
    };

    
    /**
     * \brief To be defined in CLIENT
     * \return Returns an application instance
     */
    Application* CreateApplication();
}
