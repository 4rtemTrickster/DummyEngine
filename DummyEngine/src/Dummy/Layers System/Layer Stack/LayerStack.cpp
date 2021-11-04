#include "DEpch.h"
#include "LayerStack.h"

namespace Dummy
{
    LayerStack::LayerStack()
    {
        LayersInsert = Layers.begin();
    }

    LayerStack::~LayerStack()
    {
        for(Layer* layer : Layers)
            delete layer;
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        LayersInsert = Layers.emplace(LayersInsert, layer);
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(Layers.begin(), Layers.end(), layer);

        if(it != Layers.end())
        {
            Layers.erase(it);
            --LayersInsert;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(Layers.begin(), Layers.end(), overlay);

        if(it != Layers.end()) Layers.erase(it);
    }
}
