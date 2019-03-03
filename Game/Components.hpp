
#include <unordered_map>

#include "../Engine/ECS.hpp"
#include "../Engine/Serialization.hpp"
#include "Scripts/PlayerControlSystem.hpp"
#include "Scripts/FollowEntitySystem.hpp"

auto getGameDeserializeFunctions()
{
    using namespace serialization;

    return std::unordered_map<std::string, AddDeserializedComponentFunction>
    {
        { "playerControl", addDeserializedComponent<playerControl> },
        { "followEntity", addDeserializedComponent<followEntity> }
    };
}

void initializeGameComponents(ECS * ecs)
{
    ecs->registerComponent<playerControl>();
    ecs->registerComponent<followEntity>();
}

void initializeGameSystems(ECS * ecs)
{
    ecs->registerSystem<playerControlSystem>();
    ecs->registerSystem<followEntitySystem>();
}
