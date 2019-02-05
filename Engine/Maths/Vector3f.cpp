/*
LeoTamminen
Created 31/01/2019
*/

#include <sstream>
#include "Vector3f.hpp"
#include "Basic.hpp"
#include "OStreamOperators.hpp"


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
   lhs -= rhs;
   return lhs;
}

Vector3f & Vector3f::operator*=(float f) {
   x *= f;
   y *= f;
   z *= f;

   return *this;
}

Vector3f Vector3f::operator* (float f) const {
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

Vector3f Vector3f::operator/(float f) const
{
    Vector3f lhs = *this;
    lhs /= f;
    return lhs;
}

Vector3f Vector3f::operator-() const
{
    return *this * -1;
}


float Engine::Maths::magnitude(const Vector3f &v)
{
    return (float)sqrt(v.x * v.x + v.y * v.y + v.z + v.z);
}

Vector3f Engine::Maths::cross(const Vector3f &lhs, const Vector3f &rhs)
{
    return Vector3f(
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    );
}

Vector3f Engine::Maths::normalize(const Vector3f & v)
{
    float length = magnitude(v);
    return v / length;
}

float Engine::Maths::dot(const Vector3f &lhs, const Vector3f &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
