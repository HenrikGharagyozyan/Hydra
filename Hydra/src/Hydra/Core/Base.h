#pragma once

#include <memory>
#include "Hydra/Core/PlatformDetection.h" 

// ================= DLL EXPORT / IMPORT =================
#ifdef HD_DYNAMIC_LINK
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
    #define HD_EXPAND_MACRO(x) x

    // Internal implementations of assertions with and without messages
    #define HD_ASSERT_NO_MSG(x) { if(!(x)) { HD_ERROR("Assertion Failed!"); HD_DEBUGBREAK(); } }
    #define HD_ASSERT_WITH_MSG(x, ...) { if(!(x)) { HD_ERROR("Assertion Failed: {0}", __VA_ARGS__); HD_DEBUGBREAK(); } }

    #define HD_CORE_ASSERT_NO_MSG(x) { if(!(x)) { HD_CORE_ERROR("Assertion Failed!"); HD_DEBUGBREAK(); } }
    #define HD_CORE_ASSERT_WITH_MSG(x, ...) { if(!(x)) { HD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); HD_DEBUGBREAK(); } }

    // Macro selector that counts arguments and selects the desired overload
    #define HD_GET_ASSERT_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME

    // Final macros supporting HD_ASSERT(condition) and HD_ASSERT(condition, "Fmt", args...) calls
    #define HD_ASSERT(...) HD_EXPAND_MACRO(HD_GET_ASSERT_MACRO(__VA_ARGS__, HD_ASSERT_WITH_MSG, HD_ASSERT_WITH_MSG, HD_ASSERT_WITH_MSG, HD_ASSERT_WITH_MSG, HD_ASSERT_NO_MSG)(__VA_ARGS__))
    #define HD_CORE_ASSERT(...) HD_EXPAND_MACRO(HD_GET_ASSERT_MACRO(__VA_ARGS__, HD_CORE_ASSERT_WITH_MSG, HD_CORE_ASSERT_WITH_MSG, HD_CORE_ASSERT_WITH_MSG, HD_CORE_ASSERT_WITH_MSG, HD_CORE_ASSERT_NO_MSG)(__VA_ARGS__))
#else
    #define HD_ASSERT(...)
    #define HD_CORE_ASSERT(...)
#endif


// ================= HELPERS =================
#define BIT(x) (1 << x)

#define HD_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Hydra 
{
    // Scope Wrapper
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    // Ref Wrapper
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}