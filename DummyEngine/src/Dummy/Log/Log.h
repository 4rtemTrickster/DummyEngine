#pragma once

#include "../Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Dummy
{
    class DUMMY_API Log
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:

        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
     
}


#define DE_CORE_TRACE(...)  ::Dummy::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DE_CORE_INFO(...)   ::Dummy::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DE_CORE_WARN(...)   ::Dummy::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DE_CORE_ERROR(...)  ::Dummy::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DE_CORE_FATAL(...)  ::Dummy::Log::GetCoreLogger()->critical(__VA_ARGS__)


#define DE_TRACE(...)   ::Dummy::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DE_INFO(...)    ::Dummy::Log::GetClientLogger()->info(__VA_ARGS__)
#define DE_WARN(...)    ::Dummy::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DE_ERROR(...)   ::Dummy::Log::GetClientLogger()->error(__VA_ARGS__)
#define DE_FATAL(...)   ::Dummy::Log::GetClientLogger()->critical(__VA_ARGS__)