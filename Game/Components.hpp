
#include <unordered_map>

#include "../Engine/ECS.hpp"
#include "../Engine/Serialization.hpp"
#include "Scripts/PlayerControlSystem.hpp"
#include "Scripts/FollowEntitySystem.hpp"
#include "Scripts/Camera3rdPerson.hpp"

auto getGameDeserializeFunctions()
{
    using namespace serialization;

    return std::unordered_map<std::string, AddDeserializedComponentFunction>
    {
        { "playerControl", addDeserializedComponent<playerControl> },
        { "followEntity", addDeserializedComponent<followEntity> },
        { "camera3rdPerson", addDeserializedComponent<camera3rdPerson> }
    };
}

void initializeGameComponents(ECS * ecs)
{
    ecs->registerComponent<playerControl>();
    ecs->registerComponent<followEntity>();
    ecs->registerComponent<camera3rdPerson>();
}

void initializeGameSystems(ECS * ecs)
{
    ecs->registerSystem<playerControlSystem>();
    ecs->registerSystem<followEntitySystem>();
    ecs->registerSystem<camera3rdPersonDriverSystem>();
}
