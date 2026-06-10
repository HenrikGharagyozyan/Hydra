#include "hdpch.h" 
#include "Hydra/Utils/PlatformUtils.h"
#include "Hydra/Core/Application.h"

#include <cstdio>
#include <memory>
#include <array>

namespace Hydra 
{

    std::string FileDialogs::OpenFile(const char* filter)
    {
        // Basic call to the zenity utility for file selection
        std::string command = "zenity --file-selection --title=\"Select Scene\"";
        
        // Note: Windows uses filters in the format "Hydra Scene (*.hydra)\0*.hydra\0"
        // If strict filtering by extension is needed on Linux, you can parse the filter,
        // but for a basic custom engine, a standard extension is usually added:
        command += " --file-filter=\"*.hydra\""; 

        std::string result;
        std::array<char, 256> buffer;
        
        // Open a pipe to read the output of the zenity command
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        
        if (!pipe)
        {
            return std::string();
        }

        // Read the file path returned by zenity
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        {
            result += buffer.data();
        }

        // Remove the newline character (\n) that zenity adds to the end of the path
        if (!result.empty() && result.back() == '\n')
        {
            result.pop_back();
        }

        return result;
    }

    std::string FileDialogs::SaveFile(const char* filter)
    {
        // For saving, add the --save and --confirm-overwrite (overwrite warning) flags
        std::string command = "zenity --file-selection --save --confirm-overwrite --title=\"Save Scene\"";
        command += " --file-filter=\"*.hydra\"";

        std::string result;
        std::array<char, 256> buffer;

        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        
        if (!pipe)
        {
            return std::string();
        }

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

}