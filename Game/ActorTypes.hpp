/*
Leo Tamminen
Created 21/01/2019
*/

#pragma once

#include <string>
namespace Game
{
    enum ActorType
    {
        None,
        Player,
        Fish,

        // Keep this last, so we can use it to count these
        COUNT
    };

    std::string actorTypeNames[ActorType::COUNT] =
            {
                    "NONE",
                    "PLAYER",
                    "FISH"
            };

    ActorType GetActorType(std::string name)
    {
        for (int i = 0; i < ActorType::COUNT; i++)
        {
            if (name.compare(actorTypeNames[i]) == 0)
            {
                return (ActorType) i;
            }
        }
        return ActorType::None;
    }
}