#include <Dummy.h>
#include "TestGameLayer/TestGameLayer.h"

class SandboxApp : public Dummy::Application
{
public:
    SandboxApp()
    {
        PushLayer(new TestGameLayer);
    }
};

Dummy::Application* Dummy::CreateApplication()
{
    return new SandboxApp();
}
