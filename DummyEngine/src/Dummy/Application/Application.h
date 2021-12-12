#pragma once

#include "Dummy/Core.h"
#include "Dummy/Log/Log.h"
#include "Dummy/Window/Window.h"
#include "Dummy/Event/Events/ApplicationEvent.h"
#include "Dummy/ImGui/Layer/ImGuiLayer.h"
#include "Dummy/Layers System/Layer Stack/LayerStack.h"
#include "Dummy/Layers System/Layer/Layer.h"
#include "Dummy/Timestep/Timestep.h"

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

        inline static Application& Get() { return *Instance; }
        inline Window& GetWindow() { return *window; }

    protected:

        bool OnWindowClose(WindowCloseEvent& e);
        
        std::unique_ptr<Window> window;
        ImGuiLayer* imGuiLayer;
        bool bRunning = true;

        LayerStack Layer_Stack;
        float LastFrameTime = 0.0f;

        //===========================
        static Application* Instance;
    };

    
    /**
     * \brief To be defined in CLIENT
     * \return Returns an application instance
     */
    Application* CreateApplication();
}
