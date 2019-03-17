/*
LeoTamminen
Created 03/03/2019
*/

#include "Quaternion.hpp"
#include "vector3f.hpp"
#include "matrix4f.hpp"
#include "Basic.hpp"

#include "OstreamOperators.hpp"

#include "../DEBUG.hpp"
using namespace maths;

maths::quaternion::quaternion (float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w) {}

maths::quaternion::quaternion(vector3f xyz, float w) 
    : x (xyz.x), y(xyz.y), z(xyz.z), w(w) {}

vector3f quaternion::xyz() const
{
    return vector3f(x, y, z);
}

vector3f maths::operator * (quaternion lhs, vector3f vec)
{
    auto q = lhs * quaternion(vec, 0) * inverse(lhs);
    return vector3f(q.x, q.y, q.z);
}

quaternion maths::operator * (quaternion lhs, quaternion rhs)
{
    vector3f lVec(lhs.x, lhs.y, lhs.z);
    vector3f rVec(rhs.x, rhs.y, rhs.z);

    return quaternion(
        lhs.w * rVec + rhs.w * lVec + cross(lVec, rVec),
        lhs.w * rhs.w - dot(lVec, rVec)
    );
}
  
quaternion quaternion::lookRotation(vector3f forward, vector3f up)
{
    // TODO 
    // cross of forward and global forward to get axis of major rotation
    // axis angle around that the signed angle amount
    // cross of up and forward, and cross of that and first axis to get proprly aligned up
    // rotate around forward from first axis to aligned up


    // Old way, that doesn't concern roll
    // ASSERT_VECTOR_NORMALIZED(forward)
    static const float epsAlmostOne = 0.9999f;
    float d = dot (forward, vector3f::forward);

    if (d > epsAlmostOne)
        return quaternion::identity;

    if (d < -epsAlmostOne)
        return axisAngle(up, pi);

    auto axis = normalize (cross (vector3f::forward, forward) );
    auto mainRotation = axisAngle(axis, signedAngle(vector3f::forward, forward, axis));
    return mainRotation;

    vector3f alignedUp = normalize(cross(normalize(cross(up, forward)), axis));
    float alignAngle = signedAngle(axis, alignedUp, forward);
    quaternion alignRotation = axisAngle(forward, alignAngle);

    return mainRotation * alignRotation;
}

quaternion quaternion::axisAngle(vector3f axis, float angle)
{
    angle *= 0.5f;
    return quaternion(axis * sin(angle), cos(angle));
}

float maths::magnitude(const quaternion & q)
{
    return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

quaternion maths::normalize(quaternion q)
{
    float m = magnitude(q);
    q.x /= m;
    q.y /= m;
    q.z /= m;
    q.w /= m;
    return q;
}

quaternion quaternion::eulerToQuaternion(vector3f euler)
{
    // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    // Abbreviations for the various angular functions
    // sin / cos -> yaw / pitch / roll

    euler *= deg2rad * 0.5f;
    float cy = cos(euler.z);
    float sy = sin(euler.z);
    float cp = cos(euler.y);
    float sp = sin(euler.y);
    float cr = cos(euler.x);
    float sr = sin(euler.x);

    return quaternion {
        cy * cp * sr - sy * sp * cr,
        sy * cp * sr + cy * sp * cr,
        sy * cp * cr - cy * sp * sr,
        cy * cp * cr + sy * sp * sr,
    };
}

matrix4f quaternion::toRotationMatrix(quaternion q)
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
        vector4f { 1.0f - 2.0f * (jj + kk), 2.0f * (ij + kr), 2.0f * (ik - jr), 0.0f },
        vector4f { 2.0f * (ij - kr), 1.0f - 2.0f * (ii + kk), 2.0f * (jk + ir), 0.0f },
        vector4f { 2.0f * (ik + jr), 2.0f * (jk - ir), 1.0f - 2.0f * (ii + jj), 0.0f},
        vector4f {0, 0, 0, 1}
    };
}

quaternion maths::inverse(quaternion q)
{
    q.x *= -1;
    q.y *= -1;
    q.z *= -1;
    return q;
}