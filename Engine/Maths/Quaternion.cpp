/*
LeoTamminen
Created 03/03/2019
*/

#include "Quaternion.hpp"
#include "vector3f.hpp"
#include "matrix4f.hpp"
#include "Basic.hpp"

using namespace maths;

quaternion maths::eulerToQuaternion(vector3f euler)
{
    // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    // Abbreviations for the various angular functions
    euler *= deg2rad;
    float cy = cos(euler.z * 0.5f);
    float sy = sin(euler.z * 0.5f);
    float cp = cos(euler.y * 0.5f);
    float sp = sin(euler.y * 0.5f);
    float cr = cos(euler.x * 0.5f);
    float sr = sin(euler.x * 0.5f);

    return quaternion {
        cy * cp * cr + sy * sp * sr,
        cy * cp * sr - sy * sp * cr,
        sy * cp * sr + cy * sp * cr,
        sy * cp * cr - cy * sp * sr
    };
}

quaternion maths::inverse(quaternion q)
{
    q.x *= -1;
    q.y *= -1;
    q.z *= -1;
    return q;
}

matrix4f maths::toRotationMatrix(quaternion q)
{
    float
        ii = q.x * q.x,
        jj = q.y * q.y,
        kk = q.z * q.z,
        ij = q.x * q.y,
        ik = q.x * q.z,
        jk = q.y * q.z,
        ir = q.x * q.w,
        jr = q.y * q.w,
        kr = q.z * q.w;

    // remember, columnwise, so visually this is transpose
    return matrix4f{
        vector4f { 1.0f - 2.0f * (jj * kk), 2.0f * (ij + kr), 2.0f * (ik - jr), 0.0f },
        vector4f { 2.0f * (ij - kr), 1.0f - 2.0f * (ii + kk), 2.0f * (jk + ir), 0.0f },
        vector4f { 2.0f * (ik + jr), 2.0f * (jk - ir), 1.0f - 2.0f * (ii + jj), 0.0f},
        vector4f {0, 0, 0, 1}
    };

}
