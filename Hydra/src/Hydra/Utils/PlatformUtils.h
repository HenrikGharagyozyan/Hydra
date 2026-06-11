#pragma once

#include <optional>
#include <string>

namespace Hydra
{

    class FileDialogs
    {
    public:
        // These returns empty strings if cancelled
        static std::optional<std::string> OpenFile(const char* filter);
        static std::optional<std::string> SaveFile(const char* filter);
    };

}