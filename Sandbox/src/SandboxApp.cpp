#include "Dummy.h"
#include "imgui/imgui.h"

class ExampleLayer : public Dummy::Layer
{
public:
	ExampleLayer()
		:	Layer("Example layer") {}

	void OnImGuiRender() override
	{
		
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
