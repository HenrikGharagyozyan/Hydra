#include "hdpch.h"
#include "Hydra/Core/Window.h"

#ifdef HD_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#elif defined(HD_PLATFORM_LINUX)
#include "Platform/Linux/LinuxWindow.h"
#else
#error "Unsupported platform for Hydra window creation"
#endif

namespace Hydra
{

    Scope<Window> Window::Create(const WindowProps& props)
    {
#ifdef HD_PLATFORM_WINDOWS
        return CreateScope<WindowsWindow>(props);
#elif defined(HD_PLATFORM_LINUX)
        return CreateScope<LinuxWindow>(props);
#else
        HD_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
#endif
    }

}