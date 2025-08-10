#pragma once

#ifdef HD_PLATFORM_WINDOWS
	#ifdef HD_BUILD_DLL
		#define HYDRA_API __declspec(dllexport)
	#else
		#define HYDRA_API __declspec(dllimport)
	#endif // HD_BUILD_DLL
#else
	#error Hydra only support Windows!
#endif // HD_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
