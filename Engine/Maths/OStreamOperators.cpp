/*
Leo Tamminen
Created 05/02/2019
*/

#include <iomanip>

#include "OStreamOperators.hpp"

using namespace Core::Maths;

std::ostream &operator<<(std::ostream &os, const Vector3f & v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Core::Maths::Vector4f &v)
{
    os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
    return os;
}

std::ostream & operator << (std::ostream & os, const Matrix4f & m)
{
    os << std::setprecision(4);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            os << std::setw(5) << m[j][i] << "\t";
        }
        os << "\n";
    }
    return os;
}