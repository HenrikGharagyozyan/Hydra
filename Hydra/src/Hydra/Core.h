#pragma once

#ifdef HD_PLATFORM_WINDOWS
	#ifdef HD_BUILD_DLL
		#define HYDRA_API __declspec(dllexport)
	#else
		#define HYDRA_API __declspec(dllimport)
	#endif 
#else
	#error Hydra only support Windows!
#endif 

#ifdef HD_ENABLE_ASSERTS
	#define HD_ASSERT(x, ...) { if (!(x)) { HD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HD_CORE_ASSERT(x, ...) { if (!(x)) { HD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HD_ASSERT(x, ...)
	#define HD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
