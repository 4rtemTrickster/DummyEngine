#pragma once
#include "Application/Application.h"

#ifdef DE_PLATFORM_WINDOWS

extern Dummy::Application* Dummy::CreateApplication();

int main(int argc, char** argv);

#endif