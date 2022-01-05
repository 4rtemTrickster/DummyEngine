#pragma once
#include "Dummy/Event/Event.h"
#include "Dummy/Timestep/Timestep.h"


namespace Dummy
{
    class DUMMY_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return DebugName; }
        
        protected:
        std::string DebugName;
    };
    
}
