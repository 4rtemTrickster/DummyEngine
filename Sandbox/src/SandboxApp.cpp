#include "Dummy.h"

class ExampleLayer : public Dummy::Layer
{
public:
	ExampleLayer()
		:	Layer("Exa,ple layer") {}

	void OnImGuiRender() override
	{
		if(Dummy::Input::IsKeyPressed(DE_KEY_SPACE))
			DE_INFO("Space key is pressed");
	}
};


class SandboxApp : public Dummy::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer);
		
	}
};

Dummy::Application* Dummy::CreateApplication()
{
	return new SandboxApp();
}
