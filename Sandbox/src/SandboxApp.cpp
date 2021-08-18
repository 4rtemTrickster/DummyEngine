#include "Dummy.h"

class SandboxApp : public Dummy::Application
{
	
};

int main()
{
	SandboxApp* app = new SandboxApp;

	app->Run();

	delete app;

	return 0;
}