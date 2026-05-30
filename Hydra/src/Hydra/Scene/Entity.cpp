#include "hdpch.h"
#include "Entity.h"


namespace Hydra
{

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_EntityHandle(handle)
        , m_Scene(scene)
    {
    }



}