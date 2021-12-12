#pragma once
#include "Application/Application.h"
#include "Log/Log.h"

#ifdef DE_PLATFORM_WINDOWS

extern Dummy::Application* Dummy::CreateApplication();

inline int main(int argc, char** argv);

#endif