/*
Shophorn Games
Leo Tamminen
Created 13/02/2019
*/

#pragma once

#include <vector>
#include "Collider.hpp"

namespace Engine
{
    namespace CollisionManager
    {
        void startUp();
        void shutDown();

        void addCollider(Collider * collider);
        bool testCollisions(const Collider & collider);
    }
}
