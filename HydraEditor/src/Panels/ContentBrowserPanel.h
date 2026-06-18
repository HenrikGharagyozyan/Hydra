#pragma once

#include <filesystem>


namespace Hydra
{

    class ContentBrowserPanel
    {
    public:
        ContentBrowserPanel();

        void OnImGuiRender();

    private:
        std::filesystem::path m_CurrentDirectory;
    };

}