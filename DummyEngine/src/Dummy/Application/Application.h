#pragma once

#include "Dummy/Core.h"
#include "Dummy/Log/Log.h"
#include "Dummy/Window/Window.h"
#include "Dummy/Event/Events/ApplicationEvent.h"
#include "Dummy/Layers System/Layer Stack/LayerStack.h"
#include "Dummy/Layers System/Layer/Layer.h"

namespace Dummy
{

    class DUMMY_API Application
    {
    public:

        Application();
        virtual ~Application();
        
        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

    protected:

        bool OnWindowClose(WindowCloseEvent& e);
        
        std::unique_ptr<Window> window;
        bool bRunning = true;

        LayerStack Layer_Stack;
    };

    
    /**
     * \brief To be defined in CLIENT
     * \return Returns an application instance
     */
    Application* CreateApplication();
}
