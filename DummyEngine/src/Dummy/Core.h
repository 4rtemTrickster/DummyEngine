#pragma once
 
#ifdef DE_PLATFORM_WINDOWS
	#ifdef DE_BUILD_DLL
		#define DUMMY_API __declspec(dllexport)
	#else
		#define DUMMY_API __declspec(dllimport)
	#endif
#else
	#error Dummy engine sopports only windows
#endif

#ifdef DE_ENABLE_ASSERTS
	#define DE_ASSERT(x, ...) { if(!(x)) { DE_ERROR("Assertion failed: {0}", __VA__ARGS__); __debugbreak(); } }
	#define DE_CORE_ASSERT(x, ...) { if(!(x)) { DE_CORE_ERROR("Assertion failed: {0}", __VA__ARGS__); __debugbreak(); } }
#else
	#define DE_ASSERT(x,...)
	#define DE_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1 << x)