#pragma once

// core components
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "Rendering/RendererSystem.hpp"
#include "UserInputSystem.hpp"
#include "CameraController3rdPerson.hpp"

#include "DEBUG.hpp"

inline auto getCoreDeserializeFunctions()
{
    using namespace serialization;

    return std::unordered_map<std::string, AddDeserializedComponentFunction>
    {
        { "Transform", addDeserializedComponent<transform> },
        { "Camera", addDeserializedComponent<CameraComponent> },
        { "Renderer", addDeserializedComponent<renderer> },
        { "UserInput", addDeserializedComponent<UserInput> },
        { "CameraController3rdPerson", addDeserializedComponent<CameraController3rdPerson> }
    };
}

inline void initializeCoreComponents(ECS * ecs)
{
    ecs->registerComponent<transform>();
    ecs->registerComponent<renderer>();
    ecs->registerComponent<CameraComponent>();
    ecs->registerComponent<UserInput>();
    ecs->registerComponent<CameraController3rdPerson>();
}

inline void initializeCoreSystems(ECS * ecs)
{
    ecs->registerSystem<rendererSystem>();
    ecs->registerSystem<CameraUpdateSystem>();
    ecs->registerSystem<UserInputSystem>();
    ecs->registerSystem<CameraController3rdPersonSystem>();
}