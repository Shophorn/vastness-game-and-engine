/*
LeoTamminen
Created 04/02/2019
*/

#include "Vector4f.hpp"

float & Core::Maths::Vector4f::operator[](int index) { return values [index]; }
const float & Core::Maths::Vector4f::operator[](int index) const { return values [index]; }

float Core::Maths::dot(const Core::Maths::Vector4f &lhs, const Core::Maths::Vector4f &rhs)
{
    return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2] + lhs[3] * rhs[3];
}
