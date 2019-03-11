#pragma once

// core components
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "Rendering/RendererSystem.hpp"

inline auto getCoreDeserializeFunctions()
{
    using namespace serialization;

    return std::unordered_map<std::string, AddDeserializedComponentFunction>
    {
        { "transform", addDeserializedComponent<transform> },
        { "camera", addDeserializedComponent<CameraComponent> },
        { "renderer", addDeserializedComponent<renderer> },
    };
}

inline void initializeCoreComponents(ECS * ecs)
{
    ecs->registerComponent<transform>();
    ecs->registerComponent<renderer>();
    ecs->registerComponent<CameraComponent>();
}

inline void initializeCoreSystems(ECS * ecs)
{
    ecs->registerSystem<rendererSystem>();
    ecs->registerSystem<CameraUpdateSystem>();
}