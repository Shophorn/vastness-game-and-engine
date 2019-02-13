/*
LeoTamminen
Created 13/02/2019
*/

#include "Collider.hpp"

namespace Engine::Serialization
{
    template <>
    Collider deserialize<Collider>(const Value & value)
    {
        Collider c;
        c.position = Vector3f(0);
        c.radius = value["radius"].GetFloat();
        return c;
    }
}