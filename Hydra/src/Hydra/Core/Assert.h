#pragma once

#include "Hydra/Core/Base.h"
#include "Hydra/Core/Log.h"

#include <filesystem>


#ifdef HD_ENABLE_ASSERTS

    #define HD_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { HD##type##ERROR(msg, __VA_ARGS__); HD_DEBUGBREAK(); } }
    #define HD_INTERNAL_ASSERT_WITH_MSG(type, check, ...) HD_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
    #define HD_INTERNAL_ASSERT_NO_MSG(type, check) HD_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", HD_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

    #define HD_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
    #define HD_INTERNAL_ASSERT_GET_MACRO(...) HD_EXPAND_MACRO( HD_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, HD_INTERNAL_ASSERT_WITH_MSG, HD_INTERNAL_ASSERT_NO_MSG) )

    // Currently accepts at least the condition and one additional parameter (the message) being optional
    #define HD_ASSERT(...) HD_EXPAND_MACRO( HD_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
    #define HD_CORE_ASSERT(...) HD_EXPAND_MACRO( HD_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
    #define HD_ASSERT(...)
    #define HD_CORE_ASSERT(...)
#endif