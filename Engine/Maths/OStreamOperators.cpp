/*
Leo Tamminen
Created 05/02/2019
*/

#include <iomanip>

#include "OStreamOperators.hpp"

using namespace maths;

std::ostream &operator<<(std::ostream &os, const vector3f & v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

std::ostream &operator<<(std::ostream &os, const maths::vector4f &v)
{
    return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
}

std::ostream & operator << (std::ostream & os, const matrix4f & m)
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

std::ostream &operator<<(std::ostream &os, const maths::quaternion &q)
{
    os << std::setprecision(2);
    return os << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
}
