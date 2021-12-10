#pragma once
#include "Dummy/Layers System/Layer/Layer.h"

namespace Dummy
{
    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return Layers.begin(); }
        std::vector<Layer*>::iterator end() { return Layers.end(); }

    protected:
        std::vector<Layer*> Layers;
        size_t LayersInsertIndex = 0;
    };
    
}
