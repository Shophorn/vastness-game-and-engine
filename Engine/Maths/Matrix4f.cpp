/*
LeoTamminen
Created 31/01/2019
*/

#include "Matrix4f.hpp"

using namespace Engine::Maths;

Vector3f Matrix4f::MultiplyPoint(Vector3f rhs)
{
    float z = rhs.x * _values[3] + rhs.y * _values[7] + rhs.z * _values[11] + _values[16];
    return Vector3f (
        rhs.x * _values[0] + rhs.y * _values[4] + rhs.z * _values[8] + _values[12] / z,
        rhs.x * _values[1] + rhs.y * _values[5] + rhs.z * _values[9] + _values[13] / z,
        rhs.x * _values[2] + rhs.y * _values[6] + rhs.z * _values[10] + _values[14] / z
    );
}

Vector3f Matrix4f::MultiplyDirection(Vector3f rhs)
{
    return Vector3f (
            rhs.x * _values[0] + rhs.y * _values[4] + rhs.z * _values[8],
            rhs.x * _values[1] + rhs.y * _values[5] + rhs.z * _values[9],
            rhs.x * _values[2] + rhs.y * _values[6] + rhs.z * _values[10]
    );
}

void Matrix4f::Translate(Vector3f translation)
{
    _values[12] += translation.x;
    _values[13] += translation.x;
    _values[14] += translation.x;
}

void Matrix4f::Scale(Vector3f scale)
{
    _values[0] *= scale.x;
    _values[5] *= scale.y;
    _values[10] *= scale.z;
}

void Matrix4f::Transpose()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            int a = i + 4 * j;
            int b = j + 4 * i;
            float temp = _values[a];
            _values[a] = _values[b];
            _values[b] = temp;
        }
    }
}

void Matrix4f::Invert()
{

}
