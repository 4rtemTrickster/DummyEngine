#include <Dummy.h>
#include "TestGameLayer/TestGameLayer.h"
#include "TopSystemsTestTask/TopSystemTestTaskLayer.h"

class SandboxApp : public Dummy::Application
{
public:
    SandboxApp()
    {
        //PushLayer(new TestGameLayer);
        PushLayer(new TopSystemTestTaskLayer);
    }
};

Dummy::Application* Dummy::CreateApplication()
{
    return new SandboxApp();
}
