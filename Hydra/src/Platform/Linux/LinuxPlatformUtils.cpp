#include "hdpch.h" 
#include "Hydra/Utils/PlatformUtils.h"
#include "Hydra/Core/Application.h"

#include <cstdio>
#include <memory>
#include <array>
#include <cstring> // For strlen

namespace Hydra 
{

    std::string FileDialogs::OpenFile(const char* filter)
    {
        std::string command = "zenity --file-selection --title=\"Select File\"";
        
        // Parse Windows-style filter ("Name\0*.extension\0") into Zenity format ("Name | *.extension")
        if (filter && strlen(filter) > 0)
        {
            std::string filterName(filter); 
            const char* specPtr = filter + filterName.length() + 1;
            if (*specPtr)
            {
                std::string filterSpec(specPtr);
                command += " --file-filter=\"" + filterName + " | " + filterSpec + "\"";
            }
        }
        else
        {
            command += " --file-filter=\"*.hydra\""; // Default fallback
        }

        std::string result;
        std::array<char, 256> buffer;
        
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) return std::string();

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        {
            result += buffer.data();
        }

        if (!result.empty() && result.back() == '\n')
        {
            result.pop_back();
        }

        return result;
    }

    std::string FileDialogs::SaveFile(const char* filter)
    {
        std::string command = "zenity --file-selection --save --confirm-overwrite --title=\"Save File\"";
        std::string defaultExt = ".hydra"; // Fallback if the filter is empty

        // 1. Dynamically extract filter for the dialog and the default extension
        if (filter && strlen(filter) > 0)
        {
            std::string filterName(filter); // Reads until the first \0 (e.g., "Hydra Scene (*.hydra)")
            const char* specPtr = filter + filterName.length() + 1; // Move past the \0
            
            if (*specPtr)
            {
                std::string filterSpec(specPtr); // Reads the mask (e.g., "*.hydra")
                command += " --file-filter=\"" + filterName + " | " + filterSpec + "\"";

                // Extract the extension including the dot (e.g., from "*.hydra" get ".hydra")
                size_t dotPos = filterSpec.find_last_of('.');
                if (dotPos != std::string::npos)
                {
                    defaultExt = filterSpec.substr(dotPos);
                }
            }
        }
        else
        {
            command += " --file-filter=\"*.hydra\"";
        }

        std::string result;
        std::array<char, 256> buffer;

        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) return std::string();

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        {
            result += buffer.data();
        }

        if (!result.empty() && result.back() == '\n')
        {
            result.pop_back();
        }

        // 2. FIX: Check if the user manually added the extension
        if (!result.empty() && !defaultExt.empty())
        {
            // If the string length is less than the extension or the extension at the end doesn't match
            if (result.size() < defaultExt.size() || 
                result.compare(result.size() - defaultExt.size(), defaultExt.size(), defaultExt) != 0)
            {
                result += defaultExt; // Automatically append .hydra (or any other extension)
            }
        }

        return result;
    }

}