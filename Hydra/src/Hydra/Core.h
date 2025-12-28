#pragma once

// ================= PLATFORM DETECTION =================
// Allow the build system to predefine platform macros. Only define
// them here if they are not already provided on the command line.
#if !defined(HD_PLATFORM_WINDOWS) && !defined(HD_PLATFORM_LINUX)
#if defined(_WIN32) || defined(_WIN64)
#define HD_PLATFORM_WINDOWS
#elif defined(__linux__)
#define HD_PLATFORM_LINUX
#else
#error Hydra only supports Windows and Linux!
#endif
#endif

// ================= DLL EXPORT / IMPORT =================
#ifdef HD_PLATFORM_WINDOWS
#ifdef HD_BUILD_DLL
#define HYDRA_API __declspec(dllexport)
#else
#define HYDRA_API __declspec(dllimport)
#endif
#elif defined(HD_PLATFORM_LINUX)
#ifdef HD_BUILD_DLL
#define HYDRA_API __attribute__((visibility("default")))
#else
#define HYDRA_API
#endif
#endif

// ================= DEBUG ASSERTS =================
#ifdef HD_DEBUG
#define HD_ENABLE_ASSERTS
#endif

#ifdef HD_PLATFORM_WINDOWS
#define HD_DEBUGBREAK() __debugbreak()
#elif defined(HD_PLATFORM_LINUX)
#include <signal.h>
#define HD_DEBUGBREAK() raise(SIGTRAP)
#else
#define HD_DEBUGBREAK()
#endif

#ifdef HD_ENABLE_ASSERTS
#define HD_ASSERT(x, ...)                                   \
    {                                                       \
        if (!(x))                                           \
        {                                                   \
            HD_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            HD_DEBUGBREAK();                                \
        }                                                   \
    }
#define HD_CORE_ASSERT(x, ...)                                   \
    {                                                            \
        if (!(x))                                                \
        {                                                        \
            HD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            HD_DEBUGBREAK();                                     \
        }                                                        \
    }
#else
#define HD_ASSERT(x, ...)
#define HD_CORE_ASSERT(x, ...)
#endif

// ================= HELPERS =================
#define BIT(x) (1 << x)
#define HD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
