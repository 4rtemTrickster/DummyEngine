#include "Dummy.h"


class SandboxApp : public Dummy::Application
{
	
};

Dummy::Application* Dummy::CreateApplication()
{
	return new SandboxApp();
}
