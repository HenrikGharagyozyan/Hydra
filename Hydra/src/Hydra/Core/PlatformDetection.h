#pragma once

// Platform detection using compiler-predefined macros
#ifdef _WIN32
    /* Windows x64/x86 */
    #ifdef _WIN64
        /* Windows x64 is fully supported */
        #define HD_PLATFORM_WINDOWS
    #else
        /* Windows x86 architecture is deprecated for Hydra */
        #error "x86 builds are not supported by Hydra! Please switch to x64."
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    /* * TARGET_OS_MAC exists on all Apple platforms,
     * so we must check them in strict hierarchical order.
     */
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "iOS Simulator is not supported by Hydra!"
    #elif TARGET_OS_IPHONE == 1
        #define HD_PLATFORM_IOS
        #error "iOS is not supported by Hydra!"
    #elif TARGET_OS_MAC == 1
        #define HD_PLATFORM_MACOS
        #error "macOS is currently not supported by Hydra!"
    #else
        #error "Unknown Apple platform detected!"
    #endif
#elif defined(__ANDROID__)
    #define HD_PLATFORM_ANDROID
    #error "Android is not supported by Hydra!"
#elif defined(__linux__)
    /* Linux is fully supported via Hydra's Premake build system */
    #define HD_PLATFORM_LINUX
#else
    /* Unknown toolchain or unhandled OS */
    #error "Unknown or completely unsupported platform!"
#endif