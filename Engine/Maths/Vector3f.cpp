/*
LeoTamminen
Created 31/01/2019
*/

#include <sstream>
#include "Vector3f.hpp"
#include "Basic.hpp"

using namespace Engine::Maths;

const Vector3f Vector3f::down = Vector3f(0.0f, 0.0f, -1.0f);
const Vector3f Vector3f::up = Vector3f(0.0f, 0.0f, 1.0f);
const Vector3f Vector3f::left = Vector3f(-1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::right = Vector3f(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::back = Vector3f(0.0f, -1.0f, 0.0f);
const Vector3f Vector3f::forward = Vector3f(0.0f, 1.0f, 0.0f);

Vector3f & Vector3f::operator+=(const Vector3f & rhs)
{
   x += rhs.x;
   y += rhs.y;
   z += rhs.z;

   return *this;
}

Vector3f &Vector3f::operator-=(const Vector3f &rhs)
{
   x -= rhs.x;
   y -= rhs.y;
   z -= rhs.z;

   return *this;
}

Vector3f Vector3f::operator + (const Vector3f &rhs)
{
   Vector3f lhs = *this;
   lhs += rhs;
   return lhs;
}

Vector3f Vector3f::operator-(const Vector3f &rhs) {
   Vector3f lhs = *this;
   lhs += rhs;
   return lhs;
}

Vector3f & Vector3f::operator*=(float f) {
   x *= f;
   y *= f;
   z *= f;

   return *this;
}

Vector3f Vector3f::operator* (float f) {
    Vector3f lhs = *this;
    lhs *= f;
    return lhs;
}


Vector3f & Vector3f::operator/= (float f) {
   x /= f;
   y /= f;
   z /= f;

   return *this;
}

Vector3f Vector3f::operator/(float f)
{
    Vector3f lhs = *this;
    lhs /= f;
    return lhs;
}

std::ostream &operator<<(std::ostream &os, const Vector3f &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

float Engine::Maths::Magnitude(const Vector3f & v)
{
    return (float)sqrt(v.x * v.x + v.y * v.y + v.z + v.z);
}
