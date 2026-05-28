#include "hdpch.h"
#include "Hydra/Core/Window.h"

#ifdef HD_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

// For Time
// TODO : Add Platform/Linux
#include "Platform/Windows/WindowsWindow.h"

namespace Hydra
{

    Scope<Window> Window::Create(const WindowProps &props)
    {
        // Will be like this
        // #ifdef HD_PLATFORM_WINDOWS
        //     return CreateScope<WindowsWindow>(props);
        // #else
        //     HD_CORE_ASSERT(false, "Unknown platform!");
        //     return nullptr;
        // #endif

        // For Time
        // TODO : Add Platform/Linux
        return CreateScope<WindowsWindow>(props);
    }

}