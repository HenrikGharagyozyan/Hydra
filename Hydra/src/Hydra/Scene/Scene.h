#pragma once

#include <entt.hpp>

#include "Hydra/Core/Timestep.h"

namespace Hydra
{

    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = std::string());

        void OnUpdate(Timestep ts);

    private:
        entt::registry m_Registry;

        friend class Entity;
    };

}