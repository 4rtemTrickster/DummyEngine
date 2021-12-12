#pragma once

#include "Dummy/Core.h"
#include "Dummy/Log/Log.h"
#include "Dummy/Window/Window.h"
#include "Dummy/Event/Events/ApplicationEvent.h"
#include "Dummy/ImGui/Layer/ImGuiLayer.h"
#include "Dummy/Layers System/Layer Stack/LayerStack.h"
#include "Dummy/Layers System/Layer/Layer.h"
#include "Dummy/Renderer/Buffers/IndexBuffer/IndexBuffer.h"
#include "Dummy/Renderer/Buffers/VertexBuffer/VertexBuffer.h"
#include "Dummy/Renderer/Camera/Camera.h"
#include "Dummy/Renderer/Shader/Shader.h"
#include "Dummy/Renderer/VertexArray/VertexArray.h"

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

        std::shared_ptr<VertexArray> VertexArray_;
        std::shared_ptr<Shader> shader_;

        Camera Camera_;

        //===========================
        static Application* Instance;
    };

    
    /**
     * \brief To be defined in CLIENT
     * \return Returns an application instance
     */
    Application* CreateApplication();
}
