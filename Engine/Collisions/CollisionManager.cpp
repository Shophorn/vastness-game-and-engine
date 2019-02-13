/*
LeoTamminen
Created 13/02/2019
*/

#include "CollisionManager.hpp"
#include "Collider.hpp"
#include "../Maths/Maths.hpp"

namespace
{
    using namespace Engine;

    Collider testCollider;

    bool sphereIntersect(const Collider * a, const Collider * b)
    {
        float r2 = (a->radius + b->radius) * (a->radius + b->radius);
        return sqrDistance(a->position, b->position) < r2;
    }

    std::vector<Collider*> colliders;
}


void Engine::CollisionManager::addCollider(Engine::Collider *  collider)
{
    colliders.push_back(collider);
}

bool Engine::CollisionManager::testCollisions(const Collider & collider)
{
    for (auto * other : colliders)
    {
        if (sphereIntersect(&collider, other))
        {
            return true;
        }
    }

    return false;
}

void CollisionManager::startUp()
{
    testCollider = Collider {Vector3f(-1, -5, 1), 0.5};
    colliders.push_back( &testCollider );
}
