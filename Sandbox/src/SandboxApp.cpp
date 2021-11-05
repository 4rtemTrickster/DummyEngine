#include "Dummy.h"


class SandboxApp : public Dummy::Application
{
public:
	SandboxApp()
	{
		PushOverlay(new Dummy::ImGuiLayer);
	}
};

Dummy::Application* Dummy::CreateApplication()
{
	return new SandboxApp();
}
