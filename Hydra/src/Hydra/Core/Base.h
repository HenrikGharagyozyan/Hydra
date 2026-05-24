#pragma once

#include <memory>

// ================= PLATFORM DETECTION =================
#ifdef _WIN32
    #ifdef _WIN64
        #define HD_PLATFORM_WINDOWS
    #else
        #error "x86 Builds are not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "iOS simulator is not supported!"
    #elif TARGET_OS_IPHONE == 1
        #define HD_PLATFORM_IOS
        #error "iOS is not supported!"
    #elif TARGET_OS_MAC == 1
        #define HD_PLATFORM_MACOS
        #error "MacOS is not supported!"
    #else
        #error "Unknown Apple platform!"
    #endif
#elif defined(__ANDROID__)
    #define HD_PLATFORM_ANDROID
    #error "Android is not supported!"
#elif defined(__linux__)
    #define HD_PLATFORM_LINUX
#else
    #error "Unknown platform!"
#endif

// ================= DLL EXPORT / IMPORT =================
#ifdef HD_DYNAMIC_LINK
    #ifdef HD_PLATFORM_WINDOWS
        #ifdef HZ_BUILD_DLL
            #define HYDRA_API __declspec(dllexport)
        #else
            #define HYDRA_API __declspec(dllimport)
        #endif
    #elif defined(HD_PLATFORM_LINUX)
        #ifdef HZ_BUILD_DLL
            #define HYDRA_API __attribute__((visibility("default")))
        #else
            #define HYDRA_API
        #endif
    #else
        #define HYDRA_API
    #endif
#else
    #define HYDRA_API
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
    #define HD_ASSERT(x, ...) { if(!(x)) { HD_ERROR("Assertion Failed: {0}", __VA_ARGS__); HD_DEBUGBREAK(); } }
    #define HD_CORE_ASSERT(x, ...) { if(!(x)) { HD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); HD_DEBUGBREAK(); } }
#else
    #define HD_ASSERT(x, ...)
    #define HD_CORE_ASSERT(x, ...)
#endif

// ================= HELPERS =================
#define BIT(x) (1 << x)
#define HD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hydra 
{

    // Scope
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }


    // Ref
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}