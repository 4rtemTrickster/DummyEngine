#pragma once

#include <memory>
 
// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define DE_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define DE_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define DE_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define DE_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define DE_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection


// DLL support
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
	#error Dummy only supports Windows!
#endif // End of DLL support

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