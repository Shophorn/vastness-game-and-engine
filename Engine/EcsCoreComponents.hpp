#pragma once

// core components
#include "TransformComponent.hpp"
#include "Rendering/RendererSystem.hpp"


inline auto getCoreDeserializeFunctions()
{
    using namespace serialization;

    return std::unordered_map<std::string, AddDeserializedComponentFunction>
    {
        { "transform", addDeserializedComponent<transform> },
        { "renderer", addDeserializedComponent<renderer> },
    };
}

inline void initializeCoreComponents(ECS * ecs)
{
    ecs->registerComponent<transform>();
    ecs->registerComponent<renderer>();
}

inline void initializeCoreSystems(ECS * ecs)
{
    ecs->registerSystem<rendererSystem>();
}