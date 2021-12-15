#pragma once

#include <memory>
 
#ifdef DE_PLATFORM_WINDOWS
	#if DE_DYNAMIC_LINK
		#ifdef DE_BUILD_DLL
			#define DUMMY_API __declspec(dllexport)
		#else
			#define DUMMY_API __declspec(dllimport)
		#endif
	#else
		#define DUMMY_API
#endif
#else
	#error Dummy engine sopports only windows
#endif


#ifdef DE_DEBUG
	#define DE_ENABLE_ASSERTS
#endif

#ifdef DE_ENABLE_ASSERTS
	#define DE_ASSERT(x, ...) { if(!(x)) { DE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define DE_CORE_ASSERT(x, ...) { if(!(x)) { DE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define DE_ASSERT(x,...)
	#define DE_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1 << x)

#define DE_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Dummy
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
}