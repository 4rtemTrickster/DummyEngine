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

#define BIT(x) (1 << x)