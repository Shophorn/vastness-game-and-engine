/*
Shophorn Games
Leo Tamminen
Created 31/01/2019
*/

#pragma once

#include "../Transform.hpp"
#include "../Maths/Vector3f.hpp"

namespace Engine::Physics
{
    using namespace Engine::Maths;

    class Collider
    {
    public:
        Transform * transform = nullptr;

        Vector3f size;
        Vector3f offset;

        Vector3f min;
        Vector3f max;

        void UpdateBounds()
        {
//            Vector3f position = transform->modelMatrix().MultiplyPoint(offset);
//            Vector3f extents = size / 2.0f;
//            min = position - extents;
//            max = position + extents;
        }
    };
}


