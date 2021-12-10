#include "Dummy.h"

class ExampleLayer : public Dummy::Layer
{
public:
	ExampleLayer()
		:	Layer("Example layer") {} 

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
