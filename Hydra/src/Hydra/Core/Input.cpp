#include "hdpch.h"
#include "Hydra/Core/Input.h"

#ifdef HD_PLATFORM_WINDOWS
    #include "Platform/Windows/WindowsInput.h"
#endif

// For Time 
// TODO : Add Platform/Linux
#include "Platform/Windows/WindowsInput.h"


namespace Hydra
{

    Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();

    Scope<Input> Input::Create()
    {
    // Will be like this
    // #ifdef HD_PLATFORM_WINDOWS
    //     return CreateScope<WindowsInput>();
    // #else
    //     HD_CORE_ASSERT(false, "Unknown platform!");
    //     return nullptr;
    // #endif

        // For Time 
        // TODO : Add Platform/Linux
        return CreateScope<WindowsInput>();
    }

}